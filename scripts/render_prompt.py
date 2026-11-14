#!/usr/bin/env python3
"""Phase 5 – ghép prompt cho từng unit: prompts/master_prompt.md + dữ liệu unit -> units/<id>/prompt.md

Nguồn dữ liệu:
  data/units.json            – danh sách unit (Phase 2)
  data/context/<id>.txt      – context (Phase 3; giải nén từ data_phase3.tar.gz)
  units/<id>/cfg.txt         – CFG Clang đã lọc (Phase 4). Chưa có -> prompt yêu cầu LLM tự dựng CFG
  ceres-solver/              – mã nguồn để đánh số dòng

Chạy (chỉ cần Python 3):
  python3 scripts/render_prompt.py                  # tất cả unit
  python3 scripts/render_prompt.py --smoke          # 20 unit smoke test (data/smoke_test_units.txt)
  python3 scripts/render_prompt.py --ids u0553 u0502
"""
import argparse
import json
import os
import re
from pathlib import Path

REPO = Path(os.environ.get("REPO_DIR", Path(__file__).resolve().parents[1]))
SRC = Path(os.environ.get("SRC_DIR", REPO / "ceres-solver"))
TEMPLATE = REPO / "prompts" / "master_prompt.md"
NONE = "// (không có)"

SEC = re.compile(r"^=== \[(\d+[AB]?)\. [^\]]*\] ===$", re.M)


def context_sections(uid):
    """Tách file context Phase 3 thành các mục theo số: '1', '2', '3', '4', '5', '6A', '6B', '7', '8'."""
    p = REPO / "data" / "context" / f"{uid}.txt"
    if not p.exists():
        raise SystemExit(f"Thiếu {p} – chạy: tar -xzf data_phase3.tar.gz data/context")
    parts = SEC.split(p.read_text(encoding="utf-8"))
    return {parts[i]: parts[i + 1].strip() for i in range(1, len(parts), 2)}


def source_numbered(rel_file, start, end):
    lines = (SRC / rel_file).read_text(encoding="utf-8", errors="replace").splitlines()
    width = len(str(end))
    return "\n".join(f"{i:>{width}} | {lines[i - 1]}" for i in range(start, min(end, len(lines)) + 1))


def render(template, values, has_cfg):
    # bỏ khối comment hướng dẫn ở đầu template (không gửi cho LLM)
    text = re.sub(r"\A<!--.*?-->\s*", "", template, flags=re.S)
    # {% if cfg_text %} A {% else %} B {% endif %}
    text = re.sub(r"\{% if cfg_text %\}(.*?)\{% else %\}(.*?)\{% endif %\}",
                  lambda m: m.group(1) if has_cfg else m.group(2), text, flags=re.S)
    text = re.sub(r"\{\{ (\w+) \}\}", lambda m: str(values.get(m.group(1), m.group(0))), text)
    left = re.findall(r"\{\{ \w+ \}\}|\{%.*?%\}", text)
    if left:
        raise SystemExit(f"Còn chỗ trống chưa điền: {sorted(set(left))}")
    return re.sub(r"\n{3,}", "\n\n", text).strip() + "\n"


def build(u, template):
    uid, (start, end) = u["id"], u["lines"]
    c = context_sections(uid)
    d = REPO / "units" / uid
    cfg_p = d / "cfg.txt"
    cfg = cfg_p.read_text(encoding="utf-8").strip() if cfg_p.exists() else ""
    callees = "\n".join(x for x in (c.get("6A", ""), c.get("6B", "")) if x)
    values = {
        "qualname": u["name"], "file": u["file"], "line_start": start, "line_end": end,
        "source_numbered": source_numbered(u["file"], start, end),
        "cfg_text": cfg,
        "includes": c.get("2") or NONE,
        "call_rules": c.get("3") or "- Hàm `public`, gọi trực tiếp.",
        "class_decl": c.get("4") or NONE,
        "types": c.get("5") or NONE,
        "callees": callees or NONE,
        "helpers": c.get("7") or NONE,
        "sample_tests": c.get("8") or NONE,
        "test_file_name": f"{uid}_test.cc",
    }
    d.mkdir(parents=True, exist_ok=True)
    (d / "prompt.md").write_text(render(template, values, bool(cfg)), encoding="utf-8")
    return bool(cfg)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--smoke", action="store_true", help="chỉ 20 unit trong data/smoke_test_units.txt")
    ap.add_argument("--ids", nargs="*")
    a = ap.parse_args()
    units = json.loads((REPO / "data" / "units.json").read_text(encoding="utf-8"))
    if a.smoke:
        ids = {line.split()[0] for line in (REPO / "data" / "smoke_test_units.txt").read_text(encoding="utf-8").splitlines()
               if line.strip()}
        units = [u for u in units if u["id"] in ids]
    elif a.ids:
        units = [u for u in units if u["id"] in set(a.ids)]
    template = TEMPLATE.read_text(encoding="utf-8")
    with_cfg = sum(build(u, template) for u in units)
    print(f"Đã ghép {len(units)} prompt ({with_cfg} có CFG dựng sẵn, {len(units) - with_cfg} để LLM tự dựng CFG)")


if __name__ == "__main__":
    main()
