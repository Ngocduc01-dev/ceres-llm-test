#!/usr/bin/env python3
"""Phase 1 – Xây code graph cho Ceres bằng libclang, lưu vào SQLite.

Node (bảng `nodes`):
  file      – file nguồn của Ceres
  class     – class / struct / class template có định nghĩa
  function  – hàm, method, constructor, destructor, function template

Cạnh (bảng `edges`):
  CALLS        function -> function   (hàm A gọi hàm B; count = số chỗ gọi)
  USES_TYPE    function -> class      (tham số, giá trị trả về, biến cục bộ dùng class đó)
  INHERITS     class    -> class      (kế thừa)
  MEMBER_OF    function -> class      (method thuộc class)
  DEFINED_IN   function/class -> file
  INCLUDES     file     -> file       (#include, chỉ giữa các file của Ceres)

Mỗi function có thêm thuộc tính phục vụ các phase sau: signature, kiểu tham số,
access (public/private), linkage (internal = static/anonymous namespace -> không gọi
trực tiếp từ test được), số nhánh (if/for/while/case/?:/&&/||), độ phức tạp cyclomatic.

Chạy trong container, sau build.sh:
  scripts/run_docker.sh env JOBS=6 python3 scripts/build_graph.py
Đầu ra:
  data/graph.db              – SQLite (không commit, sinh lại được)
  reports/graph/summary.txt  – thống kê
  reports/graph/stats.json   – thống kê dạng máy đọc
"""
import json
import os
import sqlite3
import sys
import time
from collections import Counter, defaultdict
from multiprocessing import Pool
from pathlib import Path

import clang.cindex as ci

REPO = Path(os.environ.get("REPO_DIR", Path(__file__).resolve().parents[1]))
SRC = Path(os.environ.get("SRC_DIR", REPO / "ceres-solver"))
DB_DIR = REPO / "data"
OUT = REPO / "reports" / "graph"
ci.Config.set_library_file(os.environ.get("LIBCLANG_PATH", "/usr/lib/llvm-18/lib/libclang.so"))

K = ci.CursorKind
FUNC_KINDS = {K.FUNCTION_DECL, K.CXX_METHOD, K.CONSTRUCTOR, K.DESTRUCTOR,
              K.FUNCTION_TEMPLATE, K.CONVERSION_FUNCTION}
CLASS_KINDS = {K.STRUCT_DECL, K.CLASS_DECL, K.UNION_DECL, K.CLASS_TEMPLATE,
               K.CLASS_TEMPLATE_PARTIAL_SPECIALIZATION}
# Các node tạo ra nhánh (dùng để đếm số nhánh / cyclomatic – ước lượng cho C2)
DECISION_KINDS = {K.IF_STMT, K.FOR_STMT, K.WHILE_STMT, K.DO_STMT, K.CASE_STMT,
                  K.CONDITIONAL_OPERATOR, K.CXX_FOR_RANGE_STMT, K.CXX_CATCH_STMT}
FUNC_IDS = {k.value for k in FUNC_KINDS}
CLASS_IDS = {k.value for k in CLASS_KINDS}
DECISION_IDS = {k.value for k in DECISION_KINDS}
CALL_ID = K.CALL_EXPR.value
TYPEREF_IDS = {K.TYPE_REF.value, K.TEMPLATE_REF.value}
BASE_ID = K.CXX_BASE_SPECIFIER.value
NAMESPACE_ID = K.NAMESPACE.value
TU_ID = K.TRANSLATION_UNIT.value


def kind_name(cur):
    try:
        return K.from_id(cur._kind_id).name
    except ValueError:
        return f"KIND_{cur._kind_id}"


def rel(path):
    return os.path.relpath(path, SRC)


def is_ceres_file(path):
    """File của Ceres. Bỏ googletest/gmock mà Ceres 2.2.0 để sẵn trong internal/ceres/."""
    p = path.replace("\\", "/")
    if "/gmock" in p or "/gtest" in p:
        return False
    return "/internal/ceres/" in p or "/include/ceres/" in p


def is_test_file(relpath):
    return (relpath.endswith("_test.cc") or "test_util" in relpath or "/gmock" in relpath
            or "/gtest/" in relpath or relpath.endswith("_test_utils.cc"))


def in_scope(relpath):
    """Cùng định nghĩa phạm vi với parse_check.py / coverage.sh."""
    return (not is_test_file(relpath) and "/generated/" not in relpath
            and "/generated_bundle_adjustment_tests/" not in relpath)


BINOP_ID = K.BINARY_OPERATOR.value


def binop(cur):
    """Toán tử của BINARY_OPERATOR (binding Python của libclang 18 chưa có thuộc tính này).
    Toán tử = token ngay sau các token của vế trái. Chỉ áp dụng cho code thật sự được compile
    (khác với đếm token trên cả hàm: sẽ tính nhầm code nằm trong #if bị tắt)."""
    toks = [t.spelling for t in cur.get_tokens()]
    if not toks:
        return None
    kids = list(cur.get_children())
    if not kids:
        return None
    n_left = sum(1 for _ in kids[0].get_tokens())
    return toks[n_left] if 0 < n_left < len(toks) else None


def qualname(cur):
    parts, c = [], cur
    while c is not None and c._kind_id != TU_ID:
        if c._kind_id == NAMESPACE_ID and not c.spelling:
            parts.append("(anonymous)")
        else:
            parts.append(c.spelling or "?")
        c = c.semantic_parent
    return "::".join(reversed(parts))


def in_anonymous_ns(cur):
    c = cur.semantic_parent
    while c is not None and c._kind_id != TU_ID:
        if c._kind_id == NAMESPACE_ID and not c.spelling:
            return True
        c = c.semantic_parent
    return False


def safe(fn, default=None):
    try:
        return fn()
    except Exception:
        return default


def clean_args(cmd):
    args = list(cmd.arguments)[1:]
    out, skip = [], False
    for a in args:
        if skip:
            skip = False
            continue
        if a in ("-o", "-c", "-MF", "-MT", "-MQ"):
            skip = a != "-c"
            continue
        if a == cmd.filename or a.endswith(os.path.basename(cmd.filename)):
            continue
        if a.startswith(("--coverage", "-fprofile", "-ftest-coverage")):
            continue
        out.append(a)
    return out


# ---------------------------------------------------------------- worker ----
_SEEN_BODIES = set()  # mỗi process con nhớ hàm đã duyệt thân (hàm trong header bị parse lại ở nhiều TU)


def func_node(cur, tu_file):
    f = rel(cur.location.file.name)
    params = [{"name": a.spelling, "type": a.type.spelling} for a in (safe(cur.get_arguments, []) or [])]
    linkage = "internal" if (in_anonymous_ns(cur) or
                             safe(lambda: cur.storage_class == ci.StorageClass.STATIC, False)
                             and cur._kind_id == K.FUNCTION_DECL.value) else "external"
    return {
        "usr": cur.get_usr(), "kind": "function", "ckind": kind_name(cur),
        "name": cur.spelling, "qualname": qualname(cur), "displayname": cur.displayname,
        "return_type": "" if cur._kind_id in (K.CONSTRUCTOR.value, K.DESTRUCTOR.value)
        else safe(lambda: cur.result_type.spelling, ""),
        "params": params, "n_params": len(params),
        "file": f, "line": cur.extent.start.line, "end_line": cur.extent.end.line,
        "is_def": int(cur.is_definition()), "is_test": int(is_test_file(f)),
        "in_scope": int(cur.is_definition() and in_scope(f)),
        # hàm tự do (không thuộc class) có access = INVALID -> để trống
        "access": (safe(lambda: cur.access_specifier.name.lower(), "") or "").replace("invalid", ""),
        "linkage": linkage,
        "is_template": int(cur._kind_id == K.FUNCTION_TEMPLATE.value),
        "is_static_method": int(safe(cur.is_static_method, False)),
        "is_virtual": int(safe(cur.is_virtual_method, False)),
        "is_pure_virtual": int(safe(cur.is_pure_virtual_method, False)),
        "is_const": int(safe(cur.is_const_method, False)),
        "parent_usr": safe(lambda: cur.semantic_parent.get_usr(), "") if
        safe(lambda: cur.semantic_parent._kind_id in CLASS_IDS, False) else "",
        "tu_file": tu_file,
    }


def analyze_body(fcur, fusr, edges, stats):
    """Duyệt thân hàm: lời gọi hàm, kiểu được dùng, số nhánh."""
    decisions, logical, ext_calls, unresolved = 0, 0, 0, 0
    calls, types = Counter(), set()
    for c in fcur.walk_preorder():
        kid = c._kind_id
        if kid in DECISION_IDS:
            decisions += 1
        elif kid == BINOP_ID:
            if binop(c) in ("&&", "||"):
                logical += 1
        elif kid == CALL_ID:
            ref = c.referenced
            if ref is None or ref._kind_id not in FUNC_IDS:
                unresolved += 1
                continue
            loc = ref.location.file
            if loc is not None and is_ceres_file(loc.name):
                calls[ref.get_usr()] += 1
                yield ("decl", ref)
            else:
                ext_calls += 1
        elif kid in TYPEREF_IDS:
            ref = c.referenced
            if ref is not None and ref._kind_id in CLASS_IDS and ref.location.file \
                    and is_ceres_file(ref.location.file.name):
                ref = safe(ref.get_definition) or ref  # forward declaration -> định nghĩa thật
                types.add(ref.get_usr())
                yield ("class", ref)
    for dst, n in calls.items():
        edges.append((fusr, dst, "CALLS", n))
    for dst in types:
        edges.append((fusr, dst, "USES_TYPE", 1))
    stats["ext_calls"] += ext_calls
    stats["unresolved_calls"] += unresolved
    stats["_attrs"] = {"decisions": decisions, "logical_ops": logical,
                       "branches": 2 * (decisions + logical),
                       "cyclomatic": 1 + decisions + logical,
                       "ext_calls": ext_calls, "unresolved_calls": unresolved}


def class_node(cur):
    f = rel(cur.location.file.name)
    return {"usr": cur.get_usr(), "kind": "class", "ckind": kind_name(cur),
            "name": cur.spelling, "qualname": qualname(cur), "file": f,
            "line": cur.extent.start.line, "end_line": cur.extent.end.line,
            "is_def": int(cur.is_definition()), "is_test": int(is_test_file(f)), "in_scope": int(in_scope(f)),
            "is_template": int(cur._kind_id in (K.CLASS_TEMPLATE.value,
                                                 K.CLASS_TEMPLATE_PARTIAL_SPECIALIZATION.value))}


def process_tu(job):
    filename, args = job
    tu_rel = rel(filename)
    index = ci.Index.create()
    t0 = time.time()
    try:
        tu = index.parse(filename, args=args, options=0)
    except ci.TranslationUnitLoadError as e:
        return {"file": tu_rel, "error": str(e)}
    nodes, edges = {}, []
    stats = Counter()

    def add_decl(cur):
        """Hàm được GỌI tới (chưa chắc đã thấy định nghĩa trong TU này).
        Đánh dấu là khai báo: nếu có định nghĩa thật, TU khác sẽ ghi đè khi gộp.
        Nhờ vậy constructor/destructor/operator= do compiler tự sinh (không có trong source)
        không bị đếm là unit."""
        u = cur.get_usr()
        if u and u not in nodes and cur.location.file:
            n = func_node(cur, tu_rel)
            n["is_def"], n["in_scope"] = 0, 0
            nodes[u] = n

    def visit(cursor):
        for ch in cursor.get_children():
            f = ch.location.file
            if f is None or not is_ceres_file(f.name):
                continue
            kid = ch._kind_id
            if kid in CLASS_IDS and ch.is_definition():
                n = class_node(ch)
                if n["usr"]:
                    nodes.setdefault(n["usr"], n)
                    edges.append((n["usr"], "file:" + n["file"], "DEFINED_IN", 1))
                    for b in ch.get_children():
                        if b._kind_id == BASE_ID and b.referenced is not None:
                            r = safe(b.referenced.get_definition) or b.referenced
                            if r.location.file and is_ceres_file(r.location.file.name):
                                nodes.setdefault(r.get_usr(), class_node(r))
                                edges.append((n["usr"], r.get_usr(), "INHERITS", 1))
                visit(ch)
                continue
            if kid in FUNC_IDS:
                u = ch.get_usr()
                if not u:
                    continue
                if ch.is_definition():
                    n = func_node(ch, tu_rel)
                    key = (u, n["file"], n["line"])
                    if key in _SEEN_BODIES:  # đã duyệt trong TU trước (hàm ở header)
                        continue
                    _SEEN_BODIES.add(key)
                    for what, ref in analyze_body(ch, u, edges, stats):
                        if what == "decl":
                            add_decl(ref)
                        else:
                            ru = ref.get_usr()
                            if ru not in nodes:
                                nodes[ru] = class_node(ref)
                    n.update(stats.pop("_attrs"))
                    nodes[u] = n
                    edges.append((u, "file:" + n["file"], "DEFINED_IN", 1))
                    if n["parent_usr"]:
                        edges.append((u, n["parent_usr"], "MEMBER_OF", 1))
                else:
                    add_decl(ch)
                continue
            visit(ch)  # namespace, extern "C", template, ...

    visit(tu.cursor)
    includes = set()
    for inc in tu.get_includes():
        if inc.source and inc.include and is_ceres_file(inc.source.name) and is_ceres_file(inc.include.name):
            includes.add((rel(inc.source.name), rel(inc.include.name)))
    n_err = sum(1 for d in tu.diagnostics if d.severity >= ci.Diagnostic.Error)
    return {"file": tu_rel, "nodes": nodes, "edges": edges, "includes": sorted(includes),
            "stats": dict(stats), "errors": n_err, "seconds": round(time.time() - t0, 1)}


# ---------------------------------------------------------------- main ------
SCHEMA = """
CREATE TABLE nodes (
  id INTEGER PRIMARY KEY, usr TEXT UNIQUE, kind TEXT, ckind TEXT, name TEXT, qualname TEXT,
  displayname TEXT, return_type TEXT, params TEXT, n_params INT,
  file TEXT, line INT, end_line INT, loc INT,
  is_def INT, is_test INT, in_scope INT, access TEXT, linkage TEXT, is_template INT,
  is_static_method INT, is_virtual INT, is_pure_virtual INT, is_const INT,
  parent_usr TEXT, tu_file TEXT,
  decisions INT, logical_ops INT, branches INT, cyclomatic INT, ext_calls INT, unresolved_calls INT,
  fan_in INT DEFAULT 0, fan_out INT DEFAULT 0, called_by_tests INT DEFAULT 0, level INT
);
CREATE TABLE edges (src INT, dst INT, kind TEXT, count INT, PRIMARY KEY (src, dst, kind));
CREATE INDEX edges_dst ON edges(dst, kind);
CREATE INDEX nodes_name ON nodes(name);
"""
COLS = ["usr", "kind", "ckind", "name", "qualname", "displayname", "return_type", "params", "n_params",
        "file", "line", "end_line", "loc", "is_def", "is_test", "in_scope", "access", "linkage",
        "is_template", "is_static_method", "is_virtual", "is_pure_virtual", "is_const",
        "parent_usr", "tu_file", "decisions", "logical_ops", "branches", "cyclomatic",
        "ext_calls", "unresolved_calls"]


def merge_node(store, n):
    """Cùng 1 USR có thể gặp ở nhiều TU (khai báo ở header, định nghĩa ở .cc) -> ưu tiên bản định nghĩa."""
    old = store.get(n["usr"])
    if old is None or (n.get("is_def") and not old.get("is_def")) or \
            (n.get("is_def") and old.get("is_def") and "decisions" in n and "decisions" not in old):
        store[n["usr"]] = n


def levels_bottom_up(fn_ids, calls):
    """Thứ tự xử lý cho Phase 2: level 0 = hàm lá (không gọi hàm Ceres nào khác).
    Gom chu trình (đệ quy, gọi vòng) thành 1 nhóm bằng Tarjan SCC rồi tính level trên DAG."""
    adj = defaultdict(set)
    for s, d in calls:
        if s in fn_ids and d in fn_ids and s != d:
            adj[s].add(d)
    index, low, on, stack, comp, out, n_comp = {}, {}, set(), [], {}, [], 0
    counter = 0
    for root in fn_ids:
        if root in index:
            continue
        work = [(root, iter(adj[root]))]
        index[root] = low[root] = counter; counter += 1
        stack.append(root); on.add(root)
        while work:
            v, it = work[-1]
            nxt = next(it, None)
            if nxt is not None:
                if nxt not in index:
                    index[nxt] = low[nxt] = counter; counter += 1
                    stack.append(nxt); on.add(nxt)
                    work.append((nxt, iter(adj[nxt])))
                elif nxt in on:
                    low[v] = min(low[v], index[nxt])
            else:
                work.pop()
                if work:
                    low[work[-1][0]] = min(low[work[-1][0]], low[v])
                if low[v] == index[v]:
                    members = []
                    while True:
                        w = stack.pop(); on.discard(w); comp[w] = n_comp; members.append(w)
                        if w == v:
                            break
                    out.append(members); n_comp += 1
    # Tarjan sinh SCC theo thứ tự ngược topo (lá trước) -> tính level lần lượt
    level_c = {}
    for c, members in enumerate(out):
        lv = 0
        for m in members:
            for d in adj[m]:
                if comp[d] != c:
                    lv = max(lv, level_c[comp[d]] + 1)
        level_c[c] = lv
    cycles = [m for m in out if len(m) > 1]
    return {v: level_c[comp[v]] for v in fn_ids}, cycles


def main():
    db = ci.CompilationDatabase.fromDirectory(str(DB_DIR))
    # is_ceres_file() đã loại gmock_gtest_all.cc, gmock_main.cc (googletest, không phải code Ceres)
    jobs = sorted((c.filename, clean_args(c)) for c in db.getAllCompileCommands()
                  if c.filename.endswith(".cc") and is_ceres_file(c.filename))
    OUT.mkdir(parents=True, exist_ok=True)
    t0 = time.time()
    nodes, edge_count, includes, tu_info = {}, Counter(), set(), []
    agg = Counter()
    with Pool(int(os.environ.get("JOBS", os.cpu_count() or 4))) as pool:
        for i, r in enumerate(pool.imap_unordered(process_tu, jobs, chunksize=2), 1):
            if "error" in r:
                tu_info.append({"file": r["file"], "error": r["error"]})
                print(f"[{i}/{len(jobs)}] {r['file']}: LỖI {r['error']}", flush=True)
                continue
            for n in r["nodes"].values():
                merge_node(nodes, n)
            for s, d, k, c in r["edges"]:
                edge_count[(s, d, k)] = max(edge_count[(s, d, k)], c)
            includes.update(r["includes"])
            agg.update(r["stats"])
            tu_info.append({"file": r["file"], "errors": r["errors"], "seconds": r["seconds"]})
            print(f"[{i}/{len(jobs)}] {r['file']}: {len(r['nodes'])} node, {len(r['edges'])} cạnh, "
                  f"{r['seconds']}s", flush=True)

    # file node
    files = {f for n in nodes.values() for f in [n["file"]]} | {f for p in includes for f in p}
    for f in files:
        nodes["file:" + f] = {"usr": "file:" + f, "kind": "file", "ckind": "FILE", "name": os.path.basename(f),
                              "qualname": f, "file": f, "line": 1, "is_def": 1,
                              "is_test": int(is_test_file(f)), "in_scope": int(in_scope(f))}
    for s, d in includes:
        edge_count[("file:" + s, "file:" + d, "INCLUDES")] = 1

    # ---- ghi SQLite
    dbp = DB_DIR / "graph.db"
    if dbp.exists():
        dbp.unlink()
    con = sqlite3.connect(dbp)
    con.executescript(SCHEMA)
    usr2id = {}
    for n in nodes.values():
        n = dict(n)
        n["params"] = json.dumps(n.get("params", []), ensure_ascii=False) if "params" in n else None
        if n.get("end_line") and n.get("line"):
            n["loc"] = n["end_line"] - n["line"] + 1
        cur = con.execute(f"INSERT INTO nodes ({','.join(COLS)}) VALUES ({','.join('?' * len(COLS))})",
                          [n.get(c) for c in COLS])
        usr2id[n["usr"]] = cur.lastrowid
    dropped = 0
    for (s, d, k), c in edge_count.items():
        if s in usr2id and d in usr2id:
            con.execute("INSERT INTO edges VALUES (?,?,?,?)", (usr2id[s], usr2id[d], k, c))
        else:
            dropped += 1
    # fan-in / fan-out (chỉ tính CALLS từ code không phải test), số chỗ test gọi trực tiếp
    con.executescript("""
      UPDATE nodes SET fan_out = (SELECT COUNT(*) FROM edges e WHERE e.src = nodes.id AND e.kind='CALLS');
      UPDATE nodes SET fan_in = (SELECT COUNT(*) FROM edges e JOIN nodes s ON s.id = e.src
                                 WHERE e.dst = nodes.id AND e.kind='CALLS' AND s.is_test = 0);
      UPDATE nodes SET called_by_tests = (SELECT COUNT(*) FROM edges e JOIN nodes s ON s.id = e.src
                                 WHERE e.dst = nodes.id AND e.kind='CALLS' AND s.is_test = 1);
    """)
    unit_ids = {r[0] for r in con.execute("SELECT id FROM nodes WHERE kind='function' AND in_scope=1")}
    calls = list(con.execute("SELECT src, dst FROM edges WHERE kind='CALLS'"))
    levels, cycles = levels_bottom_up(unit_ids, calls)
    con.executemany("UPDATE nodes SET level=? WHERE id=?", [(lv, i) for i, lv in levels.items()])
    con.commit()

    # ---- thống kê
    q = lambda sql: con.execute(sql).fetchall()
    kinds = dict(q("SELECT kind, COUNT(*) FROM nodes GROUP BY kind"))
    ekinds = dict(q("SELECT kind, COUNT(*) FROM edges GROUP BY kind"))
    units = q("SELECT COUNT(*), SUM(branches), SUM(cyclomatic) FROM nodes WHERE kind='function' AND in_scope=1")[0]
    by_ckind = dict(q("SELECT ckind, COUNT(*) FROM nodes WHERE kind='function' AND in_scope=1 GROUP BY ckind"))
    leaf = q("SELECT COUNT(*) FROM nodes WHERE kind='function' AND in_scope=1 AND level=0")[0][0]
    max_level = q("SELECT MAX(level) FROM nodes WHERE kind='function' AND in_scope=1")[0][0]
    by_level = q("SELECT level, COUNT(*) FROM nodes WHERE kind='function' AND in_scope=1 GROUP BY level ORDER BY level")
    internal = q("SELECT COUNT(*) FROM nodes WHERE kind='function' AND in_scope=1 AND linkage='internal'")[0][0]
    private = q("SELECT COUNT(*) FROM nodes WHERE kind='function' AND in_scope=1 AND access IN ('private','protected')")[0][0]
    no_branch = q("SELECT COUNT(*) FROM nodes WHERE kind='function' AND in_scope=1 AND branches=0")[0][0]
    tested = q("SELECT COUNT(*) FROM nodes WHERE kind='function' AND in_scope=1 AND called_by_tests>0")[0][0]
    top_in = q("SELECT qualname, fan_in, file FROM nodes WHERE kind='function' AND in_scope=1 ORDER BY fan_in DESC LIMIT 15")
    top_cc = q("SELECT qualname, cyclomatic, branches, file, line FROM nodes WHERE kind='function' AND in_scope=1 ORDER BY cyclomatic DESC LIMIT 15")
    top_out = q("SELECT qualname, fan_out, file FROM nodes WHERE kind='function' AND in_scope=1 ORDER BY fan_out DESC LIMIT 10")
    errs = [t for t in tu_info if t.get("error") or t.get("errors")]
    stats = {
        "ceres_version": os.environ.get("CERES_VERSION", "?"),
        "translation_units": len(jobs), "tu_with_errors": len(errs),
        "nodes_by_kind": kinds, "edges_by_kind": ekinds, "edges_dropped": dropped,
        "units": units[0], "units_by_kind": by_ckind,
        "estimated_branches_total": units[1], "cyclomatic_total": units[2],
        "units_without_branches": no_branch,
        "units_internal_linkage": internal, "units_private_or_protected": private,
        "units_called_directly_by_existing_tests": tested,
        "leaf_units_level0": leaf, "max_level": max_level, "units_by_level": dict(by_level),
        "call_cycles": len(cycles), "largest_cycle": max((len(c) for c in cycles), default=0),
        "calls_to_external_libs": agg["ext_calls"], "unresolved_calls": agg["unresolved_calls"],
        "seconds": round(time.time() - t0),
    }
    (OUT / "stats.json").write_text(json.dumps(stats, ensure_ascii=False, indent=1), encoding="utf-8")
    L = [f"Code graph – Ceres {stats['ceres_version']}",
         f"Translation unit đã parse: {len(jobs)} (lỗi: {len(errs)})",
         f"Node: {kinds}", f"Cạnh: {ekinds}",
         "", f"UNIT trong phạm vi (hàm/method có thân, không phải test/generated): {units[0]}",
         f"  theo loại: {by_ckind}",
         f"  tổng số nhánh ước lượng từ AST (2 × điểm quyết định): {units[1]}",
         f"  unit không có nhánh nào (chỉ cần gọi 1 lần là phủ hết): {no_branch}",
         f"  unit linkage nội bộ (static / anonymous namespace): {internal}",
         f"  unit private/protected: {private}",
         f"  unit được test có sẵn gọi trực tiếp: {tested}",
         f"  unit lá (level 0, không gọi hàm Ceres khác): {leaf}; level cao nhất: {max_level}",
         f"  số unit theo level: {dict(by_level)}",
         f"  chu trình gọi (đệ quy / gọi vòng): {len(cycles)}, lớn nhất {stats['largest_cycle']} hàm",
         f"Lời gọi ra thư viện ngoài (Eigen, std, glog...): {agg['ext_calls']}",
         f"Lời gọi không resolve được (template phụ thuộc kiểu...): {agg['unresolved_calls']}",
         "", "Top 15 hàm được gọi nhiều nhất (fan-in):"]
    L += [f"  {fi:4d}  {qn}  ({f})" for qn, fi, f in top_in]
    L += ["", "Top 15 hàm phức tạp nhất (cyclomatic):"]
    L += [f"  cc={cc:4d} nhánh≈{br:4d}  {qn}  ({f}:{ln})" for qn, cc, br, f, ln in top_cc]
    L += ["", "Top 10 hàm gọi nhiều hàm khác nhất (fan-out):"]
    L += [f"  {fo:4d}  {qn}  ({f})" for qn, fo, f in top_out]
    L += ["", f"Thời gian: {stats['seconds']}s"]
    (OUT / "summary.txt").write_text("\n".join(L) + "\n", encoding="utf-8")
    print("\n".join(L))
    con.close()
    return 0


if __name__ == "__main__":
    sys.exit(main())
