#!/usr/bin/env python3
"""Truy vấn code graph (data/graph.db) – dùng cho Phase 3 (gom context) và để tra cứu tay.

Ví dụ (trong container):
  python3 scripts/graph_query.py Solve                      # tìm unit theo tên
  python3 scripts/graph_query.py "ceres::internal::DoglegStrategy::ComputeStep" --hops 2
  python3 scripts/graph_query.py ComputeStep --json         # in gói context dạng JSON

Dùng trong code:
  from graph_query import Graph
  g = Graph();  u = g.find("ComputeStep")[0];  ctx = g.context(u["id"], hops=2)
"""
import argparse
import json
import os
import sqlite3
from pathlib import Path

REPO = Path(os.environ.get("REPO_DIR", Path(__file__).resolve().parents[1]))


class Graph:
    def __init__(self, db_path=None):
        self.con = sqlite3.connect(db_path or REPO / "data" / "graph.db")
        self.con.row_factory = sqlite3.Row

    def _rows(self, sql, *args):
        return [dict(r) for r in self.con.execute(sql, args)]

    def node(self, nid):
        r = self._rows("SELECT * FROM nodes WHERE id=?", nid)
        return r[0] if r else None

    def find(self, name, units_only=True):
        """Tìm theo tên ngắn (Solve) hoặc tên đầy đủ (ceres::internal::X::Solve)."""
        scope = "AND kind='function' AND in_scope=1" if units_only else ""
        rows = self._rows(f"SELECT * FROM nodes WHERE (qualname=? OR name=?) {scope} ORDER BY file, line", name, name)
        if not rows:
            rows = self._rows(f"SELECT * FROM nodes WHERE qualname LIKE ? {scope} ORDER BY file, line LIMIT 50",
                              f"%{name}%")
        return rows

    def out_edges(self, nid, kind):
        return self._rows("SELECT n.*, e.count AS edge_count FROM edges e JOIN nodes n ON n.id=e.dst "
                          "WHERE e.src=? AND e.kind=?", nid, kind)

    def in_edges(self, nid, kind):
        return self._rows("SELECT n.*, e.count AS edge_count FROM edges e JOIN nodes n ON n.id=e.src "
                          "WHERE e.dst=? AND e.kind=?", nid, kind)

    def neighbors(self, nid, hops=2, kind="CALLS", direction="out"):
        """BFS trên cạnh `kind`. Trả về {id: khoảng cách}."""
        dist, frontier = {nid: 0}, [nid]
        for h in range(1, hops + 1):
            nxt = []
            for v in frontier:
                es = self.out_edges(v, kind) if direction == "out" else self.in_edges(v, kind)
                for n in es:
                    if n["id"] not in dist:
                        dist[n["id"]] = h
                        nxt.append(n["id"])
            frontier = nxt
        dist.pop(nid)
        return dist

    def context(self, nid, hops=2):
        """Gói context cho 1 unit (đầu vào Phase 3).

        - unit: thông tin unit (signature, file, dòng, số nhánh, linkage, access)
        - klass: class chứa unit (nếu là method)
        - callees: các hàm unit gọi tới, trong `hops` bước (chỉ cần signature)
        - types: các class unit dùng (tham số, biến cục bộ...)
        - callers / test_callers: ai gọi unit này (test có sẵn nào gọi trực tiếp -> làm ví dụ few-shot)
        - headers: các header cần #include khi viết test (file của unit + class + callee trực tiếp)
        """
        u = self.node(nid)
        klass = self.out_edges(nid, "MEMBER_OF")
        callees = self.neighbors(nid, hops, "CALLS", "out")
        types = self.out_edges(nid, "USES_TYPE")
        callers = self.in_edges(nid, "CALLS")
        sig = lambda n: {"id": n["id"], "qualname": n["qualname"],
                         "signature": f"{n.get('return_type') or ''} {n['qualname']}"
                                      f"({', '.join(p['type'] for p in json.loads(n['params'] or '[]'))})".strip(),
                         "file": n["file"], "line": n["line"]}
        callee_rows = [dict(self.node(i), hop=h) for i, h in sorted(callees.items(), key=lambda x: x[1])]
        headers = {u["file"]} | {k["file"] for k in klass} | {t["file"] for t in types} | \
                  {c["file"] for c in callee_rows if c["hop"] == 1}
        headers = sorted(h for h in headers if h.endswith(".h"))
        if u["file"].endswith(".cc"):  # unit trong .cc thường có header cùng tên
            h = u["file"][:-3] + ".h"
            if self._rows("SELECT 1 FROM nodes WHERE kind='file' AND file=?", h) and h not in headers:
                headers.insert(0, h)
        return {
            "unit": {k: u[k] for k in ("id", "qualname", "displayname", "return_type", "params", "file", "line",
                                       "end_line", "loc", "access", "linkage", "is_template", "is_virtual",
                                       "is_static_method", "branches", "cyclomatic", "level", "fan_in",
                                       "called_by_tests")},
            "klass": [{"qualname": k["qualname"], "file": k["file"], "line": k["line"]} for k in klass],
            "callees": [dict(sig(c), hop=c["hop"]) for c in callee_rows],
            "types": [{"qualname": t["qualname"], "file": t["file"], "line": t["line"]} for t in types],
            "callers": [sig(c) for c in callers if not c["is_test"]],
            "test_callers": [sig(c) for c in callers if c["is_test"]],
            "headers": headers,
        }


def main():
    ap = argparse.ArgumentParser(description="Tra cứu code graph")
    ap.add_argument("name")
    ap.add_argument("--hops", type=int, default=2)
    ap.add_argument("--json", action="store_true")
    a = ap.parse_args()
    g = Graph()
    rows = g.find(a.name)
    if not rows:
        print("Không tìm thấy unit nào.")
        return
    if len(rows) > 1 and not a.json:
        print(f"{len(rows)} kết quả:")
        for r in rows[:30]:
            print(f"  [{r['id']}] {r['qualname']}  {r['file']}:{r['line']}  nhánh≈{r['branches']}")
        print("-> hiển thị kết quả đầu tiên\n")
    ctx = g.context(rows[0]["id"], a.hops)
    if a.json:
        print(json.dumps(ctx, ensure_ascii=False, indent=1))
        return
    u = ctx["unit"]
    print(f"UNIT  {u['qualname']}  ({u['file']}:{u['line']}-{u['end_line']})")
    print(f"      access={u['access'] or '-'} linkage={u['linkage']} nhánh≈{u['branches']} "
          f"cyclomatic={u['cyclomatic']} level={u['level']} fan_in={u['fan_in']} test gọi={u['called_by_tests']}")
    for title, key in (("CLASS", "klass"), ("KIỂU DÙNG", "types")):
        for k in ctx[key]:
            print(f"{title:10s} {k['qualname']}  ({k['file']}:{k['line']})")
    for c in ctx["callees"]:
        print(f"GỌI (hop {c['hop']}) {c['signature']}  ({c['file']}:{c['line']})")
    for c in ctx["callers"][:15]:
        print(f"ĐƯỢC GỌI BỞI {c['qualname']}  ({c['file']}:{c['line']})")
    for c in ctx["test_callers"][:10]:
        print(f"TEST CÓ SẴN  {c['qualname']}  ({c['file']}:{c['line']})")
    print("HEADER CẦN INCLUDE: " + ", ".join(ctx["headers"]))


if __name__ == "__main__":
    main()
