#!/usr/bin/env python3
"""Phase 1 – Xuất code graph (data/graph.db) ra 1 file HTML tương tác: reports/graph/graph.html

Mở file bằng trình duyệt (cần mạng để tải thư viện cytoscape.js từ cdnjs).
  - Khám phá unit: gõ tên hàm -> xem hàm nó gọi / hàm gọi nó / kiểu nó dùng, 1-3 bước
  - Tổng quan file: graph #include và lời gọi giữa các file
  - Kế thừa class: cây kế thừa
  - Bảng unit: toàn bộ unit, sắp xếp theo độ phức tạp, số nhánh, level...
Chạy: scripts/run_docker.sh python3 scripts/viz_graph.py   (hoặc python3 trực tiếp, chỉ cần sqlite3)
"""
import json
import os
import sqlite3
from collections import Counter
from pathlib import Path

REPO = Path(os.environ.get("REPO_DIR", Path(__file__).resolve().parents[1]))
DB = REPO / "data" / "graph.db"
OUT = REPO / "reports" / "graph"
TEMPLATE = Path(__file__).resolve().parent / "templates" / "graph.html"
EK = {"CALLS": "C", "USES_TYPE": "T", "INHERITS": "I", "MEMBER_OF": "M", "INCLUDES": "N"}


def main():
    con = sqlite3.connect(DB)
    con.row_factory = sqlite3.Row
    rows = con.execute("""SELECT * FROM nodes WHERE in_scope=1 AND is_test=0
                          AND (kind='file' OR kind='class' OR (kind='function' AND is_def=1))""").fetchall()
    keep = {r["id"] for r in rows}
    nodes = []
    for r in rows:
        n = {"i": r["id"], "t": {"function": "f", "class": "c", "file": "F"}[r["kind"]],
             "n": r["name"], "q": r["qualname"], "f": r["file"], "l": r["line"]}
        if r["kind"] == "function":
            params = ", ".join(p["type"] for p in json.loads(r["params"] or "[]"))
            n.update({"sg": f"{r['return_type'] or ''} {r['qualname']}({params})".strip(),
                      "k": r["ckind"], "br": r["branches"] or 0, "cc": r["cyclomatic"] or 1,
                      "lv": r["level"], "fi": r["fan_in"], "fo": r["fan_out"], "bt": r["called_by_tests"],
                      "lk": r["linkage"], "ac": "" if r["access"] in (None, "invalid") else r["access"],
                      "tp": r["is_template"],
                      "loc": r["loc"] or 0})
        elif r["kind"] == "class":
            n.update({"tp": r["is_template"]})
        nodes.append(n)
    edges = [[e["src"], e["dst"], EK[e["kind"]], e["count"]]
             for e in con.execute("SELECT * FROM edges WHERE kind IN ('CALLS','USES_TYPE','INHERITS','MEMBER_OF','INCLUDES')")
             if e["src"] in keep and e["dst"] in keep and e["kind"] != "DEFINED_IN"]
    # cạnh gọi gộp theo file (cho view tổng quan)
    fid = {r["file"]: r["id"] for r in rows if r["kind"] == "file"}
    nfile = {r["id"]: r["file"] for r in rows}
    fc = Counter()
    for s, d, k, c in edges:
        if k == "C":
            a, b = fid.get(nfile[s]), fid.get(nfile[d])
            if a and b and a != b:
                fc[(a, b)] += 1
    file_calls = [[a, b, c] for (a, b), c in fc.items()]
    stats = json.loads((OUT / "stats.json").read_text(encoding="utf-8"))
    data = {"stats": stats, "nodes": nodes, "edges": edges, "file_calls": file_calls}
    html = TEMPLATE.read_text(encoding="utf-8").replace(
        "/*__DATA__*/null", json.dumps(data, ensure_ascii=False, separators=(",", ":")))
    OUT.mkdir(parents=True, exist_ok=True)
    (OUT / "graph.html").write_text(html, encoding="utf-8")
    print(f"graph.html: {len(nodes)} node, {len(edges)} cạnh, {len(file_calls)} cạnh file, "
          f"{(OUT / 'graph.html').stat().st_size // 1024} KB")


if __name__ == "__main__":
    main()
