#!/usr/bin/env python3
"""Phase 5 – tạo sẵn thư mục cho từng unit: units/<id>/info.json

Mỗi unit 1 thư mục, là "tài liệu" của prompt sinh test cho unit đó:
  units/<id>/
  ├── info.json      # thông tin unit (tạo ở bước này)
  ├── cfg.txt        # Phase 4 – CFG Clang đã lọc nhiễu, gắn số dòng
  ├── prompt.md      # Phase 5 – đúng prompt đã gửi (render_prompt.py)
  ├── response.md    # Phase 5 – nguyên văn câu trả lời (generate.mjs)
  └── <id>_test.cc   # Phase 5 – file test tách từ response

Chạy (chỉ cần Python 3, không cần thư viện ngoài):
  python3 scripts/init_units.py
"""
import json
import os
from pathlib import Path

REPO = Path(os.environ.get("REPO_DIR", Path(__file__).resolve().parents[1]))
KEEP = ("id", "name", "file", "lines", "signature", "branches", "cyclomatic", "topo_level",
        "level", "callable", "access", "linkage", "template_args", "called_by_tests", "order")


def main():
    units = json.loads((REPO / "data" / "units.json").read_text(encoding="utf-8"))
    out = REPO / "units"
    for u in units:
        d = out / u["id"]
        d.mkdir(parents=True, exist_ok=True)
        info = {k: u.get(k) for k in KEEP}
        (d / "info.json").write_text(json.dumps(info, ensure_ascii=False, indent=1) + "\n", encoding="utf-8")
    print(f"Đã tạo {len(units)} thư mục trong {out}")


if __name__ == "__main__":
    main()
