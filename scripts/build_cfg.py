#!/usr/bin/env python3
"""Phase 4 – dựng CFG cho từng unit bằng Clang Static Analyzer (debug.DumpCFG) -> units/<id>/cfg.txt

Cách làm:
  1. Mỗi file .cc (translation unit) chạy Clang 1 lần với checker debug.DumpCFG, bật phân tích cả header
     (-analyzer-opt-analyze-headers), tắt checker mặc định, tắt các khối ngầm (destructor, lifetime, scope).
  2. Đọc output, chỉ giữ hàm nằm trong internal/ceres/ hoặc include/ceres/.
  3. Làm gọn: thay tham chiếu [Bx.n] bằng biểu thức thật, bỏ ép kiểu ngầm, chỉ giữ câu lệnh chính của khối,
     gom cụm macro CHECK của glog thành 1 điểm quyết định CHECK(<điều kiện>), ghi rõ nhánh T/F, gắn số dòng.
  4. Ghép hàm với unit theo (file, tên đầy đủ, tham số) -> units/<id>/cfg.txt (không lưu output thô).

Chạy trong container (cần bản build có compile_commands.json):
  scripts/run_docker.sh env JOBS=4 python3 scripts/build_cfg.py            # tất cả unit
  scripts/run_docker.sh python3 scripts/build_cfg.py --smoke               # 20 unit smoke test
  scripts/run_docker.sh python3 scripts/build_cfg.py --ids u0553
"""
import argparse
import pickle
import json
import os
import re
import shlex
import sqlite3
import subprocess
import sys
import time
from collections import Counter, defaultdict
from multiprocessing import Pool
from pathlib import Path

REPO = Path(os.environ.get("REPO_DIR", Path(__file__).resolve().parents[1]))
SRC = Path(os.environ.get("SRC_DIR", REPO / "ceres-solver"))
CLANG = os.environ.get("CLANG", "clang++-18")
ANALYZER = ["--analyze", "--analyzer-no-default-checks",
            "-Xclang", "-analyzer-checker=debug.DumpCFG",
            "-Xclang", "-analyzer-display-progress",
            "-Xclang", "-analyzer-opt-analyze-headers",
            "-Xclang", "-analyzer-config", "-Xclang",
            "cfg-implicit-dtors=false,cfg-temporary-dtors=false,cfg-lifetime=false,cfg-scopes=false,cfg-loopexit=false"]

REF = re.compile(r"\[B(\d+)\.(\d+)\]")
ANNOT_ANY = re.compile(r" \((?:ImplicitCastExpr|CXXConstructExpr|BindTemporary|OperatorCall|CStyleCastExpr|"
                       r"CXXStaticCastExpr|CXXFunctionalCastExpr|CXXMemberCallExpr|CXXOperatorCallExpr|"
                       r"CXXRecordTypedCall|NewAllocator)[^()]*\)")
TRAIL_ANNOT = re.compile(r" \((?:ImplicitCastExpr|CXXConstructExpr|CXXTemporaryObjectExpr|BindTemporary|OperatorCall|"
                         r"CStyleCastExpr|CXXStaticCastExpr|CXXFunctionalCastExpr|CXXMemberCallExpr|"
                         r"CXXOperatorCallExpr|CXXRecordTypedCall|NewAllocator|ConstructionContext)[^()]*(?:\([^()]*\)[^()]*)*\)$")


# ------------------------------------------------------------------ chạy clang
def clang_args(cmd):
    args = shlex.split(cmd["command"]) if "command" in cmd else list(cmd["arguments"])
    out, skip = [], False
    for a in args[1:]:
        if skip:
            skip = False
            continue
        if a in ("-o", "-MF", "-MT", "-MQ"):
            skip = True
            continue
        if a == "-c" or a == cmd["file"] or a.startswith(("--coverage", "-fprofile", "-ftest-coverage")):
            continue
        out.append(a)
    return out


def run_tu(job):
    """Chạy Clang cho 1 file .cc, trả về {(relpath, chữ ký): danh sách dòng CFG thô} của hàm thuộc Ceres."""
    cmd = job
    full = [CLANG] + ANALYZER + clang_args(cmd) + [cmd["file"], "-o", "/dev/null"]
    t0 = time.time()
    r = subprocess.run(full, cwd=cmd["directory"], capture_output=True, text=True, errors="replace")
    funcs, cur = {}, None
    for line in r.stderr.splitlines():
        if line.startswith("ANALYZE (Syntax): "):
            rest = line[len("ANALYZE (Syntax): "):]
            path, _, sig_decl = rest.partition(" ")
            cur = None
            if ("/internal/ceres/" in path or "/include/ceres/" in path) and "/gmock" not in path and "/gtest" not in path:
                rel = os.path.relpath(path, str(SRC))
                sig, decl = split_signature(sig_decl)
                key = (rel, sig)
                if key not in funcs:
                    funcs[key] = {"decl": decl, "lines": []}
                    cur = funcs[key]["lines"]
            continue
        if line.startswith("ANALYZE (") or line.startswith(" : ") or not line.strip():
            if line.startswith(" : "):
                cur = None
            continue
        if cur is not None:
            cur.append(line)
    return {"file": os.path.relpath(cmd["file"], str(SRC)), "funcs": funcs,
            "ok": r.returncode == 0, "err": "" if r.returncode == 0 else r.stderr[-500:],
            "seconds": round(time.time() - t0, 1)}


def split_signature(s):
    """'ns::A::f(int, double *)bool f(int a, double *b)' -> ('ns::A::f(int, double *)', 'bool f(int a, double *b)')."""
    # che các cụm có ngoặc nằm trong TÊN (không phải danh sách tham số) trước khi tìm '('
    masks = {"(anonymous namespace)": "\x01", "(anonymous class)": "\x02", "(anonymous struct)": "\x03"}
    for k, v in masks.items():
        s = s.replace(k, v)
    unmask = lambda t: [t := t.replace(v, k) for k, v in masks.items()][-1]
    start = 0
    if "operator()(" in s:
        start = s.index("operator()(") + len("operator()")
    i = s.find("(", start)
    if i < 0:
        return unmask(s), ""
    depth = 0
    for j in range(i, len(s)):
        if s[j] == "(":
            depth += 1
        elif s[j] == ")":
            depth -= 1
            if depth == 0:
                return unmask(s[:j + 1]), unmask(s[j + 1:])
    return unmask(s), ""


def name_of(sig):
    """'ns::(anonymous namespace)::f(int)' -> 'ns::(anonymous namespace)::f' (bỏ danh sách tham số)."""
    full, _ = split_signature(sig)
    depth = 0
    for j in range(len(full) - 1, -1, -1):  # tìm '(' mở của cặp ngoặc tham số cuối cùng
        if full[j] == ")":
            depth += 1
        elif full[j] == "(":
            depth -= 1
            if depth == 0:
                return full[:j]
    return full


# ------------------------------------------------------------------ làm gọn CFG
def parse_blocks(lines):
    blocks, order, cur = {}, [], None
    for line in lines:
        m = re.match(r"^ \[B(\d+)(?: \((ENTRY|EXIT)\))?\]", line)
        if m:
            cur = int(m.group(1))
            blocks[cur] = {"kind": m.group(2), "stmts": {}, "term": None, "succs": [], "preds": []}
            order.append(cur)
            continue
        if cur is None:
            continue
        s = line.strip()
        m = re.match(r"^(\d+): (.*)$", s)
        if m:
            blocks[cur]["stmts"][int(m.group(1))] = m.group(2)
        elif s.startswith("T: "):
            blocks[cur]["term"] = s[3:]
        elif s.startswith("Succs"):
            blocks[cur]["succs"] = s.split(":", 1)[1].split()
        elif s.startswith("Preds"):
            blocks[cur]["preds"] = s.split(":", 1)[1].split()
    return blocks, order


def bid_of(tok):
    """'B12' -> 12; 'B3(Unreachable)' -> 3; 'NULL' -> None."""
    m = re.match(r"^B(\d+)", tok)
    return int(m.group(1)) if m else None


def make_resolver(blocks):
    memo = {}

    def resolve(b, n, depth=0):
        key = (b, n)
        if key in memo:
            return memo[key]
        raw = blocks.get(b, {}).get("stmts", {}).get(n, "?")
        memo[key] = "…"  # chặn vòng lặp
        text = expand(TRAIL_ANNOT.sub("", raw), depth)
        memo[key] = text
        return text

    def expand(text, depth=0):
        if depth > 40:
            return text
        text = REF.sub(lambda m: resolve(int(m.group(1)), int(m.group(2)), depth + 1), text)
        text = ANNOT_ANY.sub("", text)  # nhãn chú thích của Clang còn nằm giữa biểu thức
        return text.replace("this->", "").replace("(this)->", "")

    return resolve, expand


def short(text, n=150):
    text = re.sub(r"\s+", " ", text).strip()
    return text if len(text) <= n else text[:n - 1] + "…"


def clean_cfg(sig, lines, src_lines, line_start, line_end):
    blocks, order = parse_blocks(lines)
    if not blocks:
        return None
    resolve, expand = make_resolver(blocks)
    referenced = set()
    for b in blocks.values():
        for t in list(b["stmts"].values()) + ([b["term"]] if b["term"] else []):
            referenced.update((int(x), int(y)) for x, y in REF.findall(t))

    # khối "CHECK sai" của glog: có google::LogMessageFatal(<file>, <dòng>)
    check_fail = {}
    for bid, b in blocks.items():
        joined = " ".join(b["stmts"].values())
        if "LogMessageFatal" in joined:
            text = " ".join(expand(s) for s in b["stmts"].values())
            ln = re.search(r'LogMessageFatal\("[^"]*", (\d+)', text)
            cond = re.search(r'"Check failed: (.*?) ?"', text)
            check_fail[bid] = (int(ln.group(1)) if ln else None, cond.group(1) if cond else None)
        elif "__assert_fail" in joined:  # assert(...) của C: nhánh sai gọi __assert_fail rồi dừng
            text = " ".join(expand(s) for s in b["stmts"].values())
            m = re.search(r'__assert_fail\("((?:[^"\\]|\\.)*)", "[^"]*", (\d+)', text)
            check_fail[bid] = (int(m.group(2)) if m else None, m.group(1) if m else None)

    # khối in log của glog (LOG / VLOG, không phải Fatal): google::LogMessage(<file>, <dòng>)
    log_block = {}
    for bid, b in blocks.items():
        if bid in check_fail:
            continue
        text = " ".join(expand(s) for s in b["stmts"].values())
        m = re.search(r'LogMessage\w*\("[^"]*", (\d+)', text)
        if m:
            log_block[bid] = int(m.group(1))

    def nearest_log_line(bid, depth=0):
        """Dòng của lệnh in log gần nhất phía sau khối (để gắn số dòng cho điều kiện của VLOG)."""
        if bid in log_block:
            return log_block[bid]
        if depth > 4 or bid not in blocks:
            return None
        for s in blocks[bid]["succs"]:
            n = bid_of(s)
            r = nearest_log_line(n, depth + 1) if n is not None else None
            if r:
                return r
        return None

    VLOG_PAT = re.compile(r"vlocal__|verbose_level__|InitVLOG|__extension__|FLAGS_v\b")

    def glog_free(stmts):
        """Câu lệnh thật của khối (bỏ phần do macro CHECK / VLOG của glog sinh ra)."""
        keep = [x for x in stmts if not re.search(r"google::|LogMessage", x) and not VLOG_PAT.search(x)]
        return "; ".join(x.rstrip(";") for x in keep)

    # bỏ khoảng trắng, this->, ngoặc; "1.0"/"1." -> "1" (Clang in số thực khác cách viết trong source)
    norm = lambda s: re.sub(r"(\d+)\.0*(?!\d)", r"\1", re.sub(r"\s+|this->|[()]", "", s))
    # khối quyết định của CHECK (có nhánh đi tới khối LogMessageFatal)
    check_dec = {bid for bid, b in blocks.items() if any(bid_of(s) in check_fail for s in b["succs"])}
    src_norm = {i: norm(src_lines[i - 1]) for i in range(line_start, min(line_end, len(src_lines)) + 1)}
    last = [line_start]

    def find_line(text):
        """Tìm dòng trong mã nguồn chứa câu lệnh/điều kiện; nhiều dòng khớp thì lấy dòng gần dòng vừa tìm được nhất."""
        kw = ""
        m = re.match(r"^for \(\.\.\.; (.*); \.\.\.\)$", text)
        if m:  # for (...; cond; ...) -> tìm dòng có "for(" và cond
            kw, text = "for", m.group(1)
        key = re.sub(r"^(if|while|switch)", "", norm(text))[:40]
        if len(key) < 3:
            return None
        cands = []
        for i in sorted(src_norm):  # thử 1 dòng, rồi ghép 2–3 dòng (điều kiện xuống dòng)
            if kw and kw not in src_norm[i]:
                continue
            window = "".join(src_norm.get(j, "") for j in range(i, i + 3))
            if key in src_norm[i] or (key in window and key[:12] in src_norm[i]):
                cands.append(i)
        if not cands:
            return None
        best = min(cands, key=lambda i: abs(i - last[0]))
        last[0] = best
        return best

    BARE = re.compile(r"^(operator\S+|-?\d+(\.\d+)?[a-zA-Z]*|true|false|nullptr|[A-Za-z_][\w:]*|.*(\.|->)operator [\w ]+)$")

    # ---- Bước 1: thông tin từng khối Clang -> node {kind, line, text, edges[(nhãn, khối đích)]}
    # kind: start | end | stmt | dec | pass (khối rỗng/nội bộ, sẽ bị gộp vào khối kế tiếp)
    info = {}
    for bid in order:
        b = blocks[bid]
        succ = b["succs"]
        real = [s for s in succ if bid_of(s) is not None and "Unreachable" not in s]
        if b["kind"] == "ENTRY":
            info[bid] = {"kind": "start", "edges": [("", real[0])] if real else []}
            continue
        if b["kind"] == "EXIT":
            info[bid] = {"kind": "end", "edges": []}
            continue
        if bid in check_fail:
            continue  # không thành node: nhánh "CHECK sai" trỏ thẳng tới DỪNG
        stmts = [expand(TRAIL_ANNOT.sub("", s)) for n, s in sorted(b["stmts"].items()) if (bid, n) not in referenced]
        stmts = [expand(TRAIL_ANNOT.sub("", s)) for n, s in sorted(b["stmts"].items()) if (bid, n) not in referenced]
        stmts = [s for s in stmts if not re.search(r"LogMessage|__builtin_expect|^\.\.\. ,|^\(void\)0$|static_cast<void>\(0\)", s)]
        stmts = [s for s in stmts if s.strip(" ;")]
        # biến ẩn do Clang sinh cho vòng for (x : container): __range2, __begin2, __end2
        rng = [s for s in stmts if re.search(r"__(range|begin|end)\d", s)]
        stmts = [s for s in stmts if s not in rng]
        # bỏ câu lệnh đã nằm trọn trong câu lệnh khác (vd. 'f()' và 'const int n = f();')
        stmts = [s for i, s in enumerate(stmts) if not any(i != j and s in t and s != t for j, t in enumerate(stmts))]
        # 'break;', 'continue;', 'goto' có 1 nhánh ra -> không phải điểm quyết định
        real_succ = [s for s in succ if bid_of(s) is not None and "Unreachable" not in s]
        is_decision = bool(b["term"]) and len(real_succ) >= 2
        if b["term"] and not is_decision:
            stmts.append(expand(b["term"]).rstrip(";") + ";")
        if is_decision:  # khối quyết định: chỉ cần điều kiện, bỏ mẩu rời
            stmts = [s for s in stmts if not BARE.match(s)]
        elif len(stmts) > 1:  # bỏ mẩu rời: hằng số, tên biến/hàm/operator đứng một mình
            stmts = [s for s in stmts if not BARE.match(s)] or stmts[-1:]
        body = "; ".join(s.rstrip(";") for s in stmts)
        line_no = None
        if is_decision:
            term = expand(b["term"])
            fail_succ = [s for s in succ if bid_of(s) in check_fail]
            sub = "normal"
            if fail_succ:
                # Macro CHECK/CHECK_EQ/... của glog. Không dựa vào thứ tự T/F (CHECK_op viết bằng while: T = sai),
                # mà xác định nhánh "sai" là nhánh đi tới khối LogMessageFatal.
                ln, cond = check_fail[bid_of(fail_succ[0])]
                if ln and line_start <= ln <= len(src_lines):
                    label = short(src_lines[ln - 1].split("<<")[0].strip().rstrip(";"), 100)
                else:
                    label = f"CHECK({cond})" if cond else "CHECK(…)"
                line_no = ln
                ok = [s for s in real if s != fail_succ[0]]
                edges = [("đúng", ok[0] if ok else None), ("sai", "DỪNG")]
                body, sub = glog_free(stmts), "check"
            elif VLOG_PAT.search(term + " " + " ".join(b["stmts"].values())):
                # điều kiện ẩn của macro VLOG(n) (in log hay không) – không phải logic của hàm -> bỏ, đi thẳng tiếp
                body = glog_free(stmts)
                info[bid] = ({"kind": "stmt", "line": find_line(body), "text": body, "edges": [("", real[0])]}
                             if body else {"kind": "pass", "edges": [("", real[0])]})
                continue
            else:
                m = re.match(r"^(if|while|switch) (?!\()(.*)$", term)
                if m:  # Clang in "if x != nullptr" -> "if (x != nullptr)"
                    term = f"{m.group(1)} ({m.group(2)})"
                mm = re.search(r" (&&|\|\|) \.\.\.$", term)
                if mm:
                    # Clang tách "a && b" thành 2 khối: khối này chỉ là vế trái "a". Gộp với khối điều kiện đầy đủ
                    # phía sau (C2 coi cả "a && b" là 1 điểm rẽ nhánh): && đi tiếp theo nhánh đúng, || theo nhánh sai.
                    cont = succ[0] if mm.group(1) == "&&" else (succ[1] if len(succ) > 1 else None)
                    info[bid] = ({"kind": "stmt", "line": find_line(body), "text": body, "edges": [("", cont)]}
                                 if body else {"kind": "pass", "edges": [("", cont)]})
                    continue
                label = term
                line_no = find_line(term.split(" ? ")[0])
                if term.startswith("switch") or len(succ) > 2:
                    edges = [("nhánh", s) for s in real]
                else:
                    edges = [("đúng", succ[0] if succ else None), ("sai", succ[1] if len(succ) > 1 else None)]
            info[bid] = {"kind": "dec", "sub": sub, "line": line_no, "pre": body, "text": label, "edges": edges}
        else:
            nxt = [("", real[0])] if real else []
            if b["preds"] and all(bid_of(p) in check_fail for p in b["preds"]):
                continue  # sau "CHECK sai" – không bao giờ tới được
            if bid in log_block:
                info[bid] = {"kind": "pass", "edges": nxt}  # khối in log của glog – không phải logic của hàm
                continue
            if (not stmts and rng) or (stmts and all(VLOG_PAT.search(s) for s in stmts)) or not body:
                info[bid] = {"kind": "pass", "edges": nxt}  # khối rỗng / nội bộ: gộp vào khối kế tiếp
                continue
            info[bid] = {"kind": "stmt", "line": find_line(stmts[0]), "text": body, "edges": nxt}

    # ---- Bước 2: bỏ khối rỗng (đi thẳng tới khối kế tiếp), đánh số lại 1..n theo thứ tự chạy (DFS, nhánh T trước)
    def target(tok, seen=None):
        if tok in (None, "DỪNG"):
            return tok
        t = bid_of(tok)
        seen = seen or set()
        while t in info and info[t]["kind"] == "pass" and t not in seen:
            seen.add(t)
            nx = info[t]["edges"]
            t = bid_of(nx[0][1]) if nx else None
        return t if t in info else None

    start = next((b for b, v in info.items() if v["kind"] == "start"), None)
    end = next((b for b, v in info.items() if v["kind"] == "end"), None)
    # num[t]: số node khi đi vào khối t. Khối có câu lệnh rồi mới tới điều kiện -> 2 node: câu lệnh (num) + điều kiện (cond)
    num, cond, stack = {}, {}, [target(info[start]["edges"][0][1])] if start is not None and info[start]["edges"] else []
    count = 0
    while stack:
        t = stack.pop()
        if t is None or t == "DỪNG" or t in num or t == end:
            continue
        count += 1
        num[t] = count
        if info[t]["kind"] == "dec" and info[t].get("pre"):
            count += 1
            cond[t] = count
        for _, tok in reversed(info[t]["edges"]):
            stack.append(target(tok))
    # None: nhánh đi vào lời gọi không quay về (abort, LOG(FATAL), __assert_fail) -> chương trình dừng
    name = lambda t: "DỪNG" if t in ("DỪNG", None) else ("END" if t == end else (str(num[t]) if t in num else "DỪNG"))

    decs = [t for t in num if info[t]["kind"] == "dec"]
    # CFG bất thường (assert / LOG(FATAL) / hàm luôn dừng): mọi nhánh của 1 điểm quyết định đều về DỪNG
    # -> không đưa CFG dễ gây hiểu sai vào prompt; để LLM tự dựng từ mã nguồn.
    if any(all(name(target(tok)) == "DỪNG" for _, tok in info[t]["edges"]) for t in decs):
        return None
    n_check = sum(1 for t in decs if info[t]["sub"] == "check")
    normal = [t for t in decs if info[t]["sub"] != "check"]
    # số liệu đếm như người đọc CFG: điểm rẽ nhánh, số nhánh (switch: mỗi case 1 nhánh), vòng lặp, CHECK
    clean_cfg.stats = {
        "decisions": len(normal),
        "branches": sum(len(info[t]["edges"]) for t in normal),
        "loops": sum(1 for t in normal if re.match(r"(for|while|do)\b", info[t]["text"])),
        "checks": n_check,
    }
    first = target(info[start]["edges"][0][1]) if start is not None and info[start]["edges"] else end
    if first is None:  # hàm luôn dừng ngay (không có đường tới END)
        return None

    rows = []
    for t in sorted(num, key=num.get):
        v = info[t]
        if v["kind"] == "dec":
            if t in cond:  # câu lệnh chạy trước điều kiện (cùng khối Clang) -> node riêng
                rows.append((num[t], v["pre"], f"→ {cond[t]}"))
            arrows = "   ".join(f"{lab} → {name(target(tok))}" for lab, tok in v["edges"])
            rows.append((cond.get(t, num[t]), v["text"], arrows))
        else:
            arrows = "→ " + (name(target(v["edges"][0][1])) if v["edges"] else "END")
            rows.append((num[t], v["text"], arrows))
    def readable(text):
        m = re.match(r"^for \(\.\.\.; (.*); \.\.\.\)$", text)
        if m:
            return f"vòng for, điều kiện: {m.group(1)}"
        text = re.sub(r"\s*\{$", "", text)  # "for (x : c) {" -> "for (x : c)"
        return "++ (bước tiếp của vòng for)" if text == "operator++" else text

    rows = [(n, readable(text), arrows) for n, text, arrows in rows]
    width = min(60, max((len(r[1]) for r in rows), default=10))
    out = [f"Số điểm rẽ nhánh: {len(decs) - n_check}" + (f" (và {n_check} lệnh CHECK)" if n_check else ""),
           "", f"START → {name(first)}"]
    for n, text, arrows in rows:
        parts = text.split("; ") if arrows.startswith("→") else [text]
        if len(parts) > 1:  # node có nhiều câu lệnh: mỗi câu 1 dòng, mũi tên ở câu cuối
            out.append(f"{n:<3} {parts[0]}")
            out += [f"    {x}" for x in parts[1:-1]]
            out.append(f"    {parts[-1]:<{width}}   {arrows}".rstrip())
        else:
            out.append(f"{n:<3} {text:<{width}}   {arrows}".rstrip())
    return "\n".join(out) + "\n"


def template_used(u, sig, decl=""):
    """Template: tên đã điền kiểu mà CFG được dựng (vd. 'LineManifold<3>'); không phải template -> None."""
    # hàm template: Clang ghi kiểu đã điền trong khai báo, vd. "template<> void Apply<double, Jet<double, 4>>(...)"
    fn_args = ""
    short = re.sub(r"<.*>$", "", u["name"].split("::")[-1])
    if decl.lstrip().startswith("template<>"):
        k = decl.find(short + "<")
        if k >= 0:
            depth, j = 0, k + len(short)
            for j in range(k + len(short), len(decl)):
                depth += decl[j] == "<"
                depth -= decl[j] == ">"
                if depth == 0:
                    break
            fn_args = decl[k + len(short):j + 1]
    if not (re.search(r"<.*>", name_of(sig)) or fn_args):
        return None
    used = re.sub(r"\b\w+::", "", name_of(sig).replace("(anonymous namespace)::", ""))
    fn = re.sub(r"\b\w+::", "", short + fn_args) if fn_args else ""
    if "::" in used and "<" not in used.rsplit("::", 1)[1]:
        # template nằm ở class -> ghi tên class đã điền kiểu (+ hàm, nếu hàm cũng là template)
        used = used.rsplit("::", 1)[0] + (f"::{fn}" if fn else "")
    elif fn and "<" not in used:
        used = fn
    return used


def unit_header(u, info, sig, decl=""):
    """Phần đầu cfg.txt: thông tin unit viết dễ đọc."""
    name = f"{info.get('short_name') or u['name'].split('::')[-1]}{info.get('params') or '()'}"
    name = re.sub(r"^(~?\w+)<[^()]*>(?=\()", r"\1", name)  # LineManifold<N>() -> LineManifold()
    if info.get("is_const"):
        name += " const"
    ret = info.get("return_type")
    lines = [f"UNIT {u['id']}",
             f"Hàm: {name}" + (f"  → trả về {ret}" if ret else ""),
             f"Loại: {info.get('kind') or '?'}"]
    if info.get("class"):
        lines.append(f"Thuộc class: {info['class'].replace('(anonymous)', '(namespace không tên)')}")
    else:
        ns = "::".join(u["name"].split("::")[:-1]).replace("(anonymous)", "(namespace không tên)")
        lines.append(f"Namespace: {ns or '(toàn cục)'}")
    lines.append(f"Vị trí: {u['file']}, dòng {u['lines'][0]}–{u['lines'][1]}")
    used = template_used(u, sig, decl)
    if used:
        lines.append("Ghi chú: đây là template – một số kiểu dữ liệu còn để trống, chỉ được điền khi dùng. "
                     f"CFG dưới đây dựng cho trường hợp {used}.")
    return "\n".join(lines) + "\n\n"


# ------------------------------------------------------------------ ghép unit <-> hàm
def count_args(s, i):
    """Số tham số của danh sách bắt đầu ở s[i] == '(' (không đếm dấu phẩy trong <...>, (...), {...})."""
    rest = s[i + 1:].lstrip()
    if rest.startswith(")") or re.match(r"void\s*\)", rest):
        return 0
    depth, n = 0, 1
    for ch in rest:
        if ch in "<({[":
            depth += 1
        elif ch in ">)}]":
            if depth == 0:
                break
            depth -= 1
        elif ch == "," and depth == 0:
            n += 1
    return n


def n_params(sig):
    """Số tham số trong chữ ký Clang 'ns::A::f(int, Jet<double, 4> *) const'."""
    full, _ = split_signature(sig)
    i = len(name_of(sig))
    return count_args(full, i) if full[i:i + 1] == "(" else None


def unit_decl(u, src):
    """Từ mã nguồn của unit: (số tham số, có phải hàm template không)."""
    short = re.sub(r"<.*>$", "", u["name"].split("::")[-1]) if not u["name"].split("::")[-1].startswith("operator") else u["name"].split("::")[-1]
    first = u["lines"][0]
    text = "\n".join(src[first - 1:first + 15])
    prev = src[first - 2] if first >= 2 else ""
    is_tmpl = bool(re.match(r"\s*template\s*<", src[first - 1]) or re.match(r"\s*template\s*<", prev)
                   or re.match(r"\s*template\s*<", text))
    pat = re.escape(short) + r"\s*\(" if short.startswith("operator") else rf"(?<![\w~]){re.escape(short)}\s*\("
    m = re.search(pat, text)
    if not m:
        return None, None  # vd. hàm sinh bởi macro: không đọc được khai báo
    if re.search(r">\s*::\s*~?$", text[:m.start()]) and len(re.findall(r"template\s*<", text[:m.start()])) < 2:
        is_tmpl = False  # A<N>::f(...) định nghĩa ngoài class: template là của class, không phải của hàm
    return count_args(text, m.end() - 1), is_tmpl


def set_cfg_info(d, cfg, example=None):
    """Cập nhật phần CFG trong units/<id>/info.json (các phần khác do init_units.py viết)."""
    p = d / "info.json"
    info = json.loads(p.read_text(encoding="utf-8")) if p.exists() else {}
    info["cfg"] = cfg
    info["template_example"] = example
    p.write_text(json.dumps(info, ensure_ascii=False, indent=1) + "\n", encoding="utf-8")


def strip_tmpl(s):
    """Chuẩn hoá tên để so: bỏ tham số template, '(anonymous namespace)' (Clang) = '(anonymous)' (libclang)."""
    s = s.replace("(anonymous namespace)", "(anonymous)")
    prev = None
    while prev != s:
        prev, s = s, re.sub(r"<[^<>]*>", "", s)
    return s.replace(" ", "")


NO_CFG_UNUSED = "Clang không dựng được CFG: template không được dùng ở đâu trong Ceres – LLM tự dựng"
NO_CFG_OVERLOAD = "Clang không dựng được CFG: bản overload này không được dùng ở đâu trong Ceres – LLM tự dựng"
NO_CFG_ABNORMAL = "CFG bất thường (hàm luôn dừng / assert) nên không dùng – LLM tự dựng"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--smoke", action="store_true")
    ap.add_argument("--ids", nargs="*")
    ap.add_argument("--reuse", action="store_true", help="dùng lại kết quả Clang lần chạy toàn bộ trước (data/.cfg_cache.pkl)")
    a = ap.parse_args()
    units = json.loads((REPO / "data" / "units.json").read_text(encoding="utf-8"))
    if a.smoke:
        ids = {l.split()[0] for l in (REPO / "data" / "smoke_test_units.txt").read_text(encoding="utf-8").splitlines() if l.strip()}
        units = [u for u in units if u["id"] in ids]
    elif a.ids:
        units = [u for u in units if u["id"] in set(a.ids)]

    con = sqlite3.connect(REPO / "data" / "graph.db")
    node = {r[0]: r[1:] for r in con.execute("SELECT id, tu_file, params FROM nodes WHERE kind='function'")}
    db = {os.path.relpath(c["file"], str(SRC)): c for c in json.loads((REPO / "data" / "compile_commands.json").read_text())}

    # chọn translation unit cho từng unit: file .cc của chính nó, hoặc TU đã include header (từ graph.db)
    tu_of = {}
    for u in units:
        tu, _ = node.get(u["graph_id"], (None, None))
        cand = [u["file"]] if u["file"].endswith(".cc") else []
        cand += [tu] if tu else []
        tu_of[u["id"]] = next((c for c in cand if c in db), None)
    tus = sorted({t for t in tu_of.values() if t})
    if not (a.smoke or a.ids):
        # Chạy toàn bộ: dùng MỌI file .cc của Ceres (kể cả test). Template chỉ có CFG khi được instantiate,
        # và file test thường là nơi instantiate template trong header.
        tus = sorted(t for t in db if ("internal/ceres/" in t) and "gmock" not in t and "gtest" not in t)
    print(f"{len(units)} unit, cần chạy Clang trên {len(tus)} file .cc", flush=True)

    funcs = {}
    t0 = time.time()
    cache = REPO / "data" / ".cfg_cache.pkl"
    if a.reuse and cache.exists():
        funcs, tus = pickle.loads(cache.read_bytes()), []
    with Pool(int(os.environ.get("JOBS", 4))) as pool:
        for i, r in enumerate(pool.imap_unordered(run_tu, [db[t] for t in tus]), 1):
            for k, v in r["funcs"].items():
                funcs.setdefault(k, v)
            print(f"[{i}/{len(tus)}] {r['file']}: {len(r['funcs'])} hàm Ceres, {r['seconds']}s"
                  + ("" if r["ok"] else f"  LỖI: {r['err'][-200:]}"), flush=True)

    if tus and not (a.smoke or a.ids):
        cache.write_bytes(pickle.dumps(funcs))
    by_name = defaultdict(list)
    for (rel, sig), v in funcs.items():
        by_name[(rel, strip_tmpl(name_of(sig)))].append((sig, v))

    stats = Counter()
    src_cache = {}
    unmatched = []
    for u in units:
        key = (u["file"], strip_tmpl(u["name"]))
        # Chọn đúng overload: cùng số tham số, cùng tên tham số, và cùng loại (hàm template hay không).
        # Không khớp -> coi như không có CFG (KHÔNG lấy đại 1 overload khác – vd. u0018 trước đây lấy nhầm
        # Evaluate 5 tham số cho Evaluate 3 tham số chưa bao giờ được dùng).
        _, params = node.get(u["graph_id"], (None, "[]"))
        names = [p["name"] for p in json.loads(params or "[]") if p.get("name")]
        if u["file"] not in src_cache:
            src_cache[u["file"]] = (SRC / u["file"]).read_text(encoding="utf-8", errors="replace").splitlines()
        src = src_cache[u["file"]]
        n_src, unit_is_ftmpl = unit_decl(u, src)
        cands = [c for c in by_name.get(key, [])
                 if (n_src is None or n_params(c[0]) in (None, n_src))
                 and all(re.search(rf"\b{re.escape(n)}\b", c[1]["decl"]) for n in names)
                 and (unit_is_ftmpl is None or c[1]["decl"].lstrip().startswith("template<>") == unit_is_ftmpl)]
        d = REPO / "units" / u["id"]
        d.mkdir(parents=True, exist_ok=True)
        if not cands:
            if by_name.get(key):
                unmatched.append({"id": u["id"], "n": n_src, "names": names, "ftmpl": unit_is_ftmpl,
                                  "cands": [[c[0], n_params(c[0]), c[1]["decl"][:150]] for c in by_name[key]]})
            stats["không tìm thấy CFG"] += 1
            (d / "cfg.txt").unlink(missing_ok=True)
            set_cfg_info(d, {"has_cfg": False, "reason": NO_CFG_OVERLOAD if by_name.get(key) else NO_CFG_UNUSED})
            continue
        sig, v = cands[0]
        text = clean_cfg(sig, v["lines"], src_cache[u["file"]], u["lines"][0], u["lines"][1])
        if not text:  # CFG bất thường (assert / LOG(FATAL) / luôn dừng) -> để LLM tự dựng
            stats["CFG bất thường (bỏ)"] += 1
            (d / "cfg.txt").unlink(missing_ok=True)
            set_cfg_info(d, {"has_cfg": False, "reason": NO_CFG_ABNORMAL})
            continue
        info_p = d / "info.json"
        uinfo = json.loads(info_p.read_text(encoding="utf-8")) if info_p.exists() else {}
        (d / "cfg.txt").write_text(unit_header(u, uinfo, sig, v.get("decl", "")) + text, encoding="utf-8")
        stats["có CFG"] += 1
        set_cfg_info(d, {"has_cfg": True, **clean_cfg.stats}, template_used(u, sig, v.get("decl", "")))

    summary = (f"Unit: {len(units)} | có CFG: {stats['có CFG']} | không tìm thấy: {stats['không tìm thấy CFG']} | "
               f"CFG bất thường (bỏ, để LLM tự dựng): {stats['CFG bất thường (bỏ)']} | thời gian: {time.time() - t0:.0f}s")
    print(summary)
    out = REPO / "reports" / "cfg"
    out.mkdir(parents=True, exist_ok=True)
    missing = [u["id"] + " " + u["name"] + " " + u["file"] for u in units if not (REPO / "units" / u["id"] / "cfg.txt").exists()]
    (out / "unmatched.json").write_text(json.dumps(unmatched, ensure_ascii=False, indent=1), encoding="utf-8")
    (out / "summary.txt").write_text(summary + "\n\nUnit không có CFG:\n" + "\n".join(missing) + "\n", encoding="utf-8")


if __name__ == "__main__":
    sys.exit(main())
