#!/usr/bin/env python3
import json
import os
import re
import sqlite3
from collections import Counter

DB_PATH = "data/graph.db"
OUT_UNITS = "data/units.json"
OUT_SUMMARY = "reports/units/summary.txt"
OUT_SMOKE = "data/smoke_test_units.txt"

HARD_TYPES = {
    "Problem", "CostFunction", "LossFunction", "LinearSolver",
    "SparseMatrix", "BlockSparseMatrix", "CompressedRowSparseMatrix",
    "TripletSparseMatrix", "ContextImpl", "ThreadPool", "Evaluator",
    "Minimizer", "TrustRegionStrategy", "LineSearch", "IterationCallback",
    "Covariance", "Manifold", "LocalParameterization"
}

MEDIUM_KEYWORDS = (
    "Eigen::", "Matrix", "Vector", "Array", "std::vector",
    "std::string", "std::map", "std::set", "std::unordered_",
    "std::pair", "std::tuple", "std::unique_ptr", "std::shared_ptr",
    "Jet<", "ceres::"
)

def get_columns(conn, table):
    cur = conn.execute(f"PRAGMA table_info({table})")
    return [row[1] for row in cur.fetchall()]

def classify_difficulty(sig, param_types, used_types):
    params_only = sig.split("(", 1)[1] if "(" in (sig or "") else (param_types or "")
    combined = f"{params_only} {' '.join(used_types)}"
    for ht in HARD_TYPES:
        if re.search(rf"\b{re.escape(ht)}\b", combined):
            return "kho"
    for mk in MEDIUM_KEYWORDS:
        if mk in combined:
            return "trung_binh"
    tokens = re.findall(r"\b[A-Z][A-Za-z0-9_]+\b", param_types or "")
    ignored = {"FILE", "NULL", "TRUE", "FALSE", "T", "Scalar"}
    if any(t not in ignored for t in tokens):
        return "trung_binh"
    return "de"

def infer_template_args(sig, is_template):
    if not is_template and "<" not in (sig or "").split("(")[0]:
        return None
    if "Jet" in (sig or ""):
        return ["ceres::Jet<double, 4>"]
    return ["double"]

def main():
    if not os.path.exists(DB_PATH):
        raise FileNotFoundError(f"Không tìm thấy {DB_PATH}. Hãy chạy Phase 1 trước.")

    conn = sqlite3.connect(DB_PATH)
    conn.row_factory = sqlite3.Row

    node_cols = set(get_columns(conn, "nodes"))
    edge_cols = set(get_columns(conn, "edges"))

    src_col = "source" if "source" in edge_cols else ("from_id" if "from_id" in edge_cols else "src")
    dst_col = "target" if "target" in edge_cols else ("to_id" if "to_id" in edge_cols else "dst")
    type_col = "type" if "type" in edge_cols else "kind"

    all_nodes = {row["id"]: dict(row) for row in conn.execute("SELECT * FROM nodes")}
    used_types_map = {}
    member_of_map = {}

    for row in conn.execute(f"SELECT {src_col} AS s, {dst_col} AS t, {type_col} AS k FROM edges"):
        k = (row["k"] or "").upper()
        if k == "USES_TYPE":
            target_node = all_nodes.get(row["t"], {})
            t_name = target_node.get("name") or target_node.get("qualname") or ""
            used_types_map.setdefault(row["s"], []).append(t_name)
        elif k == "MEMBER_OF":
            member_of_map[row["s"]] = row["t"]

    units_raw = []
    for nid, n in all_nodes.items():
        ntype = (n.get("type") or n.get("kind") or "").lower()
        if ntype != "function":
            continue
        if "in_scope" in node_cols and n.get("in_scope") != 1:
            continue

        name = n.get("qualname") or n.get("name") or f"func_{nid}"
        file_path = n.get("file") or n.get("file_path") or ""
        start_line = n.get("start_line") or n.get("line_start") or n.get("line") or 0
        end_line = n.get("end_line") or n.get("line_end") or start_line
        sig = n.get("signature") or name
        param_types = n.get("param_types") or n.get("params") or ""
        branches = int(n.get("branches") or 0)
        cyclomatic = int(n.get("cyclomatic") or (branches // 2 + 1))
        topo_level = int(n.get("level") or 0)
        access = (n.get("access") or "public").lower()
        linkage = (n.get("linkage") or "external").lower()
        called_by_tests = int(n.get("called_by_tests") or 0)
        fan_in = int(n.get("fan_in") or 0)
        fan_out = int(n.get("fan_out") or 0)

        callable_kind = "internal" if (linkage == "internal" or access in ("private", "protected")) else "public"
        used_types = used_types_map.get(nid, [])
        difficulty = classify_difficulty(sig, param_types, used_types)

        parent_cls = all_nodes.get(member_of_map.get(nid), {})
        is_tmpl = bool(n.get("is_template") or parent_cls.get("is_template"))
        template_args = infer_template_args(sig, is_tmpl)

        units_raw.append({
            "graph_id": nid,
            "name": name,
            "file": file_path,
            "lines": [int(start_line), int(end_line)],
            "signature": sig,
            "branches": branches,
            "cyclomatic": cyclomatic,
            "topo_level": topo_level,
            "level": difficulty,
            "callable": callable_kind,
            "access": access,
            "linkage": linkage,
            "called_by_tests": called_by_tests,
            "fan_in": fan_in,
            "fan_out": fan_out,
            "template_args": template_args,
        })

    diff_rank = {"de": 0, "trung_binh": 1, "kho": 2}
    units_raw.sort(key=lambda u: (
        u["topo_level"],
        diff_rank[u["level"]],
        0 if u["callable"] == "public" else 1,
        u["branches"],
        u["file"],
        u["lines"][0]
    ))

    units_out = []
    for idx, u in enumerate(units_raw, start=1):
        u_clean = {"id": f"u{idx:04d}", **u, "order": idx}
        units_out.append(u_clean)

    os.makedirs(os.path.dirname(OUT_UNITS), exist_ok=True)
    os.makedirs(os.path.dirname(OUT_SUMMARY), exist_ok=True)

    with open(OUT_UNITS, "w", encoding="utf-8") as f:
        json.dump(units_out, f, indent=2, ensure_ascii=False)

    smoke_candidates = [
        u for u in units_out
        if u["topo_level"] == 0 and u["level"] == "de" and u["callable"] == "public" and u["branches"] >= 2 and "numeric_limits" not in u["name"]
    ]
    smoke_candidates.sort(key=lambda u: (-u["called_by_tests"], u["branches"], u["order"]))
    smoke_top20 = smoke_candidates[:20]

    with open(OUT_SMOKE, "w", encoding="utf-8") as f:
        for u in smoke_top20:
            f.write(f"{u['id']}\t{u['name']}\t{u['file']}:{u['lines'][0]}\tbranches={u['branches']}\ttests={u['called_by_tests']}\n")

    diff_cnt = Counter(u["level"] for u in units_out)
    call_cnt = Counter(u["callable"] for u in units_out)
    tmpl_cnt = sum(1 for u in units_out if u["template_args"] is not None)
    tested_cnt = sum(1 for u in units_out if u["called_by_tests"] > 0)

    lines = [
        "=== BÁO CÁO PHASE 2: LIỆT KÊ & PHÂN LOẠI UNIT ===",
        f"Tổng số unit trong phạm vi: {len(units_out)}",
        "",
        "1. Phân loại theo độ khó (level):",
        f"   - Dễ (de)          : {diff_cnt['de']} ({diff_cnt['de']*100/max(len(units_out),1):.1f}%)",
        f"   - Trung bình       : {diff_cnt['trung_binh']} ({diff_cnt['trung_binh']*100/max(len(units_out),1):.1f}%)",
        f"   - Khó (kho)        : {diff_cnt['kho']} ({diff_cnt['kho']*100/max(len(units_out),1):.1f}%)",
        "",
        "2. Khả năng gọi trực tiếp (callable):",
        f"   - Public           : {call_cnt['public']}",
        f"   - Internal         : {call_cnt['internal']} (static / anonymous namespace / private / protected)",
        "",
        "3. Đặc điểm bổ sung:",
        f"   - Unit template    : {tmpl_cnt}",
        f"   - Có test mẫu sẵn  : {tested_cnt}",
        f"   - Tập smoke test   : {len(smoke_top20)} unit xuất ra {OUT_SMOKE}",
    ]
    summary_text = "\n".join(lines) + "\n"
    with open(OUT_SUMMARY, "w", encoding="utf-8") as f:
        f.write(summary_text)
    print(summary_text)

if __name__ == "__main__":
    main()
