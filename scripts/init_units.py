#!/usr/bin/env python3
"""Phase 5 – tạo sẵn thư mục cho từng unit: units/<id>/info.json

Mỗi unit 1 thư mục, là "tài liệu" của prompt sinh test cho unit đó:
  units/<id>/
  ├── info.json      # thông tin unit (tạo ở bước này)
  ├── source.cc      # Phase 5 – mã nguồn của unit, chỉ để xem (render_prompt.py)
  ├── cfg.txt        # Phase 4 – CFG (scripts/build_cfg.py)
  ├── prompt.md      # Phase 5 – đúng prompt đã gửi (render_prompt.py)
  ├── response.md    # Phase 5 – nguyên văn câu trả lời (generate.mjs)
  └── <id>_test.cc   # Phase 5 – file test tách từ response

Chạy (chỉ cần Python 3):
  python3 scripts/init_units.py
"""
import json
import os
import re
import sqlite3
from pathlib import Path

REPO = Path(os.environ.get("REPO_DIR", Path(__file__).resolve().parents[1]))
SRC = Path(os.environ.get("SRC_DIR", REPO / "ceres-solver"))
KEEP = ("id", "name", "file", "lines", "branches", "cyclomatic", "topo_level",
        "level", "callable", "access", "linkage", "template_args", "called_by_tests", "order")
KIND = {"CXX_METHOD": "method (hàm thành viên của class)", "CONSTRUCTOR": "constructor (hàm khởi tạo)",
        "DESTRUCTOR": "destructor (hàm huỷ)", "FUNCTION_DECL": "hàm tự do (không thuộc class)",
        "FUNCTION_TEMPLATE": "hàm template (hàm mẫu, kiểu dữ liệu được điền khi dùng)",
        "CONVERSION_FUNCTION": "hàm chuyển kiểu"}


def params_from_source(u, short, cache={}):
    """Danh sách tham số đọc thẳng từ mã nguồn (graph.db không có tham số của hàm template)."""
    if not short.startswith("operator"):
        short = re.sub(r"<.*>$", "", short)
    if u["file"] not in cache:
        cache[u["file"]] = (SRC / u["file"]).read_text(encoding="utf-8", errors="replace").splitlines()
    first = u["lines"][0]
    text = "\n".join(cache[u["file"]][first - 1:first + 15])
    pat = re.escape(short) + r"\s*\(" if short.startswith("operator") else rf"(?<![\w~]){re.escape(short)}(<[^()]*>)?\s*\("
    m = re.search(pat, text)
    if not m:
        return None
    depth, i = 0, m.end() - 1
    for j in range(i, len(text)):
        depth += text[j] == "("
        depth -= text[j] == ")"
        if depth == 0:
            inner = re.sub(r"//[^\n]*", "", text[i + 1:j])
            return "(" + re.sub(r"\s+", " ", inner).strip() + ")"
    return None


def main():
    units = json.loads((REPO / "data" / "units.json").read_text(encoding="utf-8"))
    con = sqlite3.connect(REPO / "data" / "graph.db")
    con.row_factory = sqlite3.Row
    out = REPO / "units"
    for u in units:
        r = con.execute("SELECT * FROM nodes WHERE id=?", (u["graph_id"],)).fetchone()
        params = json.loads(r["params"] or "[]") if r else []
        parent = con.execute("SELECT qualname, is_template FROM nodes WHERE usr=?", (r["parent_usr"],)).fetchone() \
            if r and r["parent_usr"] else None
        info = {k: u.get(k) for k in KEEP}
        info.update({
            "short_name": r["name"] if r else u["name"].split("::")[-1],
            "kind": KIND.get(r["ckind"], r["ckind"]) if r else None,
            "class": parent["qualname"] if parent else None,
            "class_is_template": bool(parent["is_template"]) if parent else False,
            "params": ("(" + ", ".join(f"{p['type']} {p['name']}".strip() for p in params) + ")") if params
                      else (params_from_source(u, r["name"] if r else u["name"].split("::")[-1])
                           or "(xem mã nguồn – hàm được sinh ra từ macro)"),
            "return_type": (r["return_type"] or None) if r else None,
            "is_const": bool(r["is_const"]) if r else False,
        })
        d = out / u["id"]
        d.mkdir(parents=True, exist_ok=True)
        (d / "info.json").write_text(json.dumps(info, ensure_ascii=False, indent=1) + "\n", encoding="utf-8")
    print(f"Đã tạo/cập nhật {len(units)} thư mục trong {out}")


if __name__ == "__main__":
    main()
