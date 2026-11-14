#!/usr/bin/env python3
import json, os, re
from pathlib import Path
from graph_query import Graph

REPO = Path(os.environ.get("REPO_DIR", Path(__file__).resolve().parents[1]))
SRC_DIR = Path(os.environ.get("SRC_DIR", REPO / "ceres-solver"))
UNITS_FILE = REPO / "data" / "units.json"
OUT_DIR = REPO / "data" / "context"
MAX_TOKENS = 7500

def est_tokens(text: str) -> int:
    return len(text) // 3

def read_file_lines(rel_path: str, start: int, end: int) -> str:
    p = SRC_DIR / rel_path
    if not p.exists(): return ""
    lines = p.read_text(encoding="utf-8", errors="ignore").splitlines()
    return "\n".join(lines[max(0, start - 1) : min(len(lines), end)])

def extract_brace_block(rel_path: str, start_line: int, max_lines: int = 90) -> str:
    p = SRC_DIR / rel_path
    if not p.exists(): return ""
    lines = p.read_text(encoding="utf-8", errors="ignore").splitlines()
    s = max(0, start_line - 1)
    snippet = "\n".join(lines[s : min(len(lines), s + max_lines)])
    depth, started, out = 0, False, []
    for ch in snippet:
        out.append(ch)
        if ch == "{": depth += 1; started = True
        elif ch == "}":
            depth -= 1
            if started and depth == 0: break
    res = "".join(out)
    if started and depth == 0 and len(snippet) > len(res) and snippet[len(res)] == ";":
        res += ";"
    return res

def format_include(h: str) -> str:
    for pre in ("include/", "internal/"):
        if h.startswith(pre): return f'#include "{h[len(pre):]}"'
    return f'#include "{h}"'

def build_access(u: dict, ug: dict) -> str:
    ck = u.get("callable", "public")
    lnk = ug.get("linkage", "external")
    acc = ug.get("access") or "public"
    res = []
    if lnk == "internal" or ck in ("static", "anonymous_namespace"):
        res.append(f'- Internal ({ck}): `#include "{u["file"]}"` trực tiếp.')
    elif acc in ("private", "protected") or ck in ("private", "protected"):
        res.append(f'- Quyền `{acc}`: thêm `#define private public` trước `#include`.')
    else:
        res.append("- Hàm `public`, gọi trực tiếp.")
    if u.get("template_args"):
        res.append(f"- Template: instantiate với `{', '.join(u['template_args'])}`.")
    return "\n".join(res)

def build_unit_context(u: dict, g: Graph) -> tuple[str, int]:
    ctx = g.context(u["graph_id"], hops=2)
    s_l, e_l = u["lines"]
    sec1 = f"=== [1. TARGET: {u['name']}] ===\n" + read_file_lines(u["file"], max(1, s_l - 2), e_l)
    incs = ['#include "gtest/gtest.h"'] + [format_include(h) for h in ctx["headers"]]
    sec2 = "=== [2. INCLUDES] ===\n" + "\n".join(dict.fromkeys(incs))
    sec3 = "=== [3. CALL RULES] ===\n" + build_access(u, ctx["unit"])
    k_b = [extract_brace_block(k["file"], k["line"], 120) for k in ctx["klass"]]
    sec4 = "=== [4. CLASS] ===\n" + "\n\n".join(b for b in k_b if b) if k_b else ""
    t_b = [extract_brace_block(t["file"], t["line"], 120) for t in ctx["types"] if not t["qualname"].startswith(("std::", "Eigen::"))]
    sec5 = "=== [5. TYPES] ===\n" + "\n\n".join(b for b in t_b[:5] if b) if t_b else ""
    h1 = [f"{c['signature']};" for c in ctx["callees"] if c["hop"] == 1]
    h2 = [f"{c['signature']};" for c in ctx["callees"] if c["hop"] == 2]
    sec6a = "=== [6A. CALLEES HOP 1] ===\n" + "\n".join(h1[:20]) if h1 else ""
    sec6b = "=== [6B. CALLEES HOP 2] ===\n" + "\n".join(h2[:20]) if h2 else ""
    h_dir = REPO / "helpers"
    h_txts = [f.read_text(errors="ignore") for f in sorted(h_dir.glob("*.h"))] if h_dir.exists() else []
    sec7 = "=== [7. HELPERS] ===\n" + "\n\n".join(h_txts) if h_txts else ""
    smps = [extract_brace_block(tc["file"], max(1, tc["line"] - 2), 45) for tc in ctx["test_callers"][:2]]
    sec8 = "=== [8. SAMPLE TESTS] ===\n" + "\n\n".join(b for b in smps if b) if smps else ""

    mand = [s for s in (sec1, sec2, sec3, sec4, sec6a, sec7) if s]
    opt = [s for s in (sec5, sec6b, sec8) if s]  # pop() từ cuối: sec8 -> sec6b -> sec5
    secs = mand + opt
    full = "\n\n".join(secs)
    while est_tokens(full) > MAX_TOKENS and opt:
        secs.remove(opt.pop())
        full = "\n\n".join(secs)
    return full, est_tokens(full)

def main():
    OUT_DIR.mkdir(parents=True, exist_ok=True)
    units = json.loads(UNITS_FILE.read_text(encoding="utf-8"))
    g = Graph()
    stats = []
    for u in units:
        txt, tok = build_unit_context(u, g)
        (OUT_DIR / f"{u['id']}.txt").write_text(txt, encoding="utf-8")
        stats.append((u["id"], tok))
    avg_t = sum(x[1] for x in stats) / len(stats) if stats else 0
    max_u, max_t = max(stats, key=lambda x: x[1]) if stats else ("-", 0)
    summary = f"Tổng file: {len(stats)} | Token TB: {avg_t:.0f} | Token max: {max_t} ({max_u})\n"
    print(summary)
    (REPO / "reports" / "context").mkdir(parents=True, exist_ok=True)
    (REPO / "reports" / "context" / "summary.txt").write_text(summary, encoding="utf-8")

if __name__ == "__main__":
    main()
