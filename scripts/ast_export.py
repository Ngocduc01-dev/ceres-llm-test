#!/usr/bin/env python3
"""Phase 1 – Xuất AST (cây cú pháp) của một số unit ra reports/ast/ast.html để xem trực quan.

Mặc định chọn tự động từ data/graph.db:
  - TOP unit phức tạp nhất (cyclomatic cao, mỗi file tối đa 2 unit)
  - một số unit nhỏ có vài nhánh (dễ đọc, dùng làm ví dụ)
Hoặc chỉ định:  --units ComputeStep Solve "ceres::internal::Program::IsValid"

Chạy trong container, sau build_graph.py:
  scripts/run_docker.sh env JOBS=6 python3 scripts/ast_export.py
"""
import argparse
import json
import os
import sqlite3
import sys
from multiprocessing import Pool
from pathlib import Path

import clang.cindex as ci

sys.path.insert(0, str(Path(__file__).resolve().parent))
from build_graph import (BINOP_ID, DB_DIR, DECISION_IDS, FUNC_IDS, REPO, SRC,  # noqa: E402
                         binop, clean_args, is_ceres_file, kind_name, rel, safe)

OUT = REPO / "reports" / "ast"
TEMPLATE = Path(__file__).resolve().parent / "templates" / "ast.html"
MAX_NODES = 2500
COLLAPSE = {ci.CursorKind.UNEXPOSED_EXPR.value}  # nút bọc ngầm (ép kiểu ngầm...) có 1 con -> bỏ qua cho dễ đọc


def to_json(cur, budget):
    """Chuyển cursor -> dict. budget = [số node còn được phép] (giới hạn kích thước)."""
    kids = list(cur.get_children())
    while cur._kind_id in COLLAPSE and len(kids) == 1:
        cur, kids = kids[0], list(kids[0].get_children())
    budget[0] -= 1
    n = {"k": kind_name(cur), "l": cur.extent.start.line, "e": cur.extent.end.line}
    if cur.spelling:
        n["s"] = cur.spelling
    op = safe(lambda: binop(cur), None) if cur._kind_id == BINOP_ID else None
    if op:
        n["op"] = op
        if op in ("&&", "||"):
            n["d"] = 1  # && || cũng tạo nhánh (short-circuit) -> tô đỏ như if/for
    t = safe(lambda: cur.type.spelling, "")
    if t and cur._kind_id not in FUNC_IDS and len(t) < 80:
        n["t"] = t
    if cur._kind_id in DECISION_IDS:
        n["d"] = 1
    ch = []
    for k in kids:
        if budget[0] <= 0:
            n["cut"] = 1
            break
        ch.append(to_json(k, budget))
    if ch:
        n["c"] = ch
    return n


def export_tu(job):
    tu_file, args, targets = job  # targets: [(usr, file, line, id)]
    tu = ci.Index.create().parse(str(SRC / tu_file), args=args, options=0)
    want = {(f, line): (usr, nid) for usr, f, line, nid in targets}
    found = {}

    def visit(c):
        for ch in c.get_children():
            f = ch.location.file
            if f is None or not is_ceres_file(f.name):
                continue
            key = (rel(f.name), ch.extent.start.line)
            if ch._kind_id in FUNC_IDS and ch.is_definition() and key in want and want[key][0] == ch.get_usr():
                budget = [MAX_NODES]
                found[want[key][1]] = {"ast": to_json(ch, budget), "truncated": budget[0] <= 0}
                continue
            if ch._kind_id not in FUNC_IDS:
                visit(ch)
    visit(tu.cursor)
    return found


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--units", nargs="*", default=None)
    ap.add_argument("--top", type=int, default=24)
    ap.add_argument("--small", type=int, default=12)
    a = ap.parse_args()
    con = sqlite3.connect(DB_DIR / "graph.db")
    con.row_factory = sqlite3.Row
    base = "SELECT * FROM nodes WHERE kind='function' AND in_scope=1 AND is_def=1"
    if a.units:
        rows = []
        for u in a.units:
            rows += con.execute(base + " AND (qualname=? OR name=?) LIMIT 3", (u, u)).fetchall()
    else:
        per_file, rows = {}, []
        for r in con.execute(base + " AND branches>0 ORDER BY cyclomatic DESC"):
            if per_file.get(r["file"], 0) < 2 and r["loc"] and r["loc"] < 400:
                rows.append(r); per_file[r["file"]] = per_file.get(r["file"], 0) + 1
            if len(rows) >= a.top:
                break
        small = con.execute(base + " AND branches BETWEEN 2 AND 8 AND loc BETWEEN 6 AND 40 "
                                   "AND file LIKE '%.cc' ORDER BY file, line").fetchall()
        step = max(1, len(small) // max(1, a.small))
        rows += small[::step][:a.small]
    cmds = {rel(c.filename): clean_args(c) for c in
            ci.CompilationDatabase.fromDirectory(str(DB_DIR)).getAllCompileCommands()}
    jobs = {}
    for r in rows:
        tu = r["tu_file"] if r["tu_file"] in cmds else r["file"]
        if tu not in cmds:
            print(f"  bỏ qua {r['qualname']}: không có lệnh compile cho {tu}")
            continue
        jobs.setdefault(tu, []).append((r["usr"], r["file"], r["line"], r["id"]))
    found = {}
    with Pool(int(os.environ.get("JOBS", 4))) as pool:
        for res in pool.imap_unordered(export_tu, [(tu, cmds[tu], t) for tu, t in jobs.items()]):
            found.update(res)
    units = []
    for r in rows:
        if r["id"] not in found:
            continue
        lines = (SRC / r["file"]).read_text(encoding="utf-8", errors="replace").splitlines()
        units.append({"id": r["id"], "q": r["qualname"], "f": r["file"], "l": r["line"], "e": r["end_line"],
                      "br": r["branches"], "cc": r["cyclomatic"], "lv": r["level"],
                      "src": lines[r["line"] - 1:r["end_line"]], **found[r["id"]]})
    data = {"ceres_version": os.environ.get("CERES_VERSION", "?"), "units": units}
    OUT.mkdir(parents=True, exist_ok=True)
    html = TEMPLATE.read_text(encoding="utf-8").replace(
        "/*__DATA__*/null", json.dumps(data, ensure_ascii=False, separators=(",", ":")))
    (OUT / "ast.html").write_text(html, encoding="utf-8")
    print(f"ast.html: {len(units)} unit, {(OUT / 'ast.html').stat().st_size // 1024} KB")


if __name__ == "__main__":
    main()
