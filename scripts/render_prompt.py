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


def include_path(rel):
    """Đường dẫn #include theo thư mục include của Ceres: internal/ceres/x.cc -> ceres/x.cc."""
    for pre in ("internal/", "include/"):
        if rel.startswith(pre):
            return rel[len(pre):]
    return rel


def unit_info_block(u, info):
    """Thông tin unit, viết dễ đọc (đầu mục 3.1)."""
    name = f"{info.get('short_name') or u['name'].split('::')[-1]}{info.get('params') or '()'}"
    name = re.sub(r"^(~?\w+)<[^()]*>(?=\()", r"\1", name)  # LineManifold<N>() -> LineManifold()
    if info.get("is_const"):
        name += " const"
    lines = [f"- Hàm: `{name}`" + (f", trả về `{info['return_type']}`" if info.get("return_type") else "")]
    if info.get("kind"):
        lines.append(f"- Loại: {info['kind']}")
    if info.get("class"):
        lines.append(f"- Thuộc class: `{info['class']}`" + (" (class template)" if info.get("class_is_template") else ""))
    else:
        lines.append(f"- Namespace: `{'::'.join(u['name'].split('::')[:-1]) or '(toàn cục)'}`")
    lines.append(f"- Vị trí: `{u['file']}`, dòng {u['lines'][0]}–{u['lines'][1]}")
    return "\n".join(lines).replace("(anonymous)", "(namespace không tên)")


def call_rules(u, info):
    """Cách gọi unit trong file test, viết bằng lời đơn giản."""
    rules = []
    if info.get("linkage") == "internal" or u.get("linkage") == "internal":
        rules.append(f"- Hàm này chỉ dùng được bên trong file `{u['file']}` (khai báo `static` hoặc trong namespace "
                     f"không tên). Để gọi được, thêm `#include \"{include_path(u['file'])}\"` vào file test.")
    if (u.get("access") or "") in ("private", "protected"):
        rules.append(f"- Method này là `{u['access']}` (bên ngoài class không gọi được). Thêm 2 dòng "
                     "`#define private public` và `#define protected public` **sau** `#include \"gtest/gtest.h\"` "
                     "và **trước** các `#include` của Ceres.")
    if info.get("class"):
        rules.append(f"- Đây là method của class `{info['class']}`: tạo một object của class rồi gọi method trên object đó.")
    if u.get("template_args") or info.get("class_is_template"):
        rules.append("- Đây là template (khuôn mẫu): khi tạo object hoặc gọi hàm phải chọn kiểu cụ thể phù hợp "
                     "(xem ví dụ chỗ dùng trong Ceres ở ghi chú của CFG, nếu có).")
    if not rules:
        rules.append("- Hàm gọi trực tiếp được.")
    return "\n".join(rules).replace("(anonymous)", "(namespace không tên)")


def build(u, template):
    uid, (start, end) = u["id"], u["lines"]
    c = context_sections(uid)
    d = REPO / "units" / uid
    info_p = d / "info.json"
    info = json.loads(info_p.read_text(encoding="utf-8")) if info_p.exists() else {}
    cfg_p = d / "cfg.txt"
    cfg = ""
    if cfg_p.exists():
        # cfg.txt = [thông tin unit] + dòng trống + [CFG]. Thông tin unit đã có ở 3.1 -> chỉ giữ ghi chú template + CFG
        head, _, body = cfg_p.read_text(encoding="utf-8").strip().partition("\n\n")
        note = [l for l in head.splitlines() if l.startswith("Ghi chú:")]
        cfg = "\n".join(note + ([""] if note else []) + [body.strip()])
    includes = [l for l in (c.get("2") or "").splitlines() if l.strip()]
    if (info.get("linkage") == "internal" or u.get("linkage") == "internal"):
        inc = f'#include "{include_path(u["file"])}"'
        if inc not in includes:
            includes.append(inc)
    values = {
        "source_numbered": source_numbered(u["file"], start, end),
        "unit_info": unit_info_block(u, info),
        "cfg_text": cfg,
        "includes": "\n".join(includes) or '#include "gtest/gtest.h"',
        "call_rules": call_rules(u, info),
        "test_file_name": f"{uid}_test.cc",
    }
    d.mkdir(parents=True, exist_ok=True)
    # mã nguồn của unit, để xem nhanh (không compile; chỉ là đoạn trích từ file gốc)
    src = (SRC / u["file"]).read_text(encoding="utf-8", errors="replace").splitlines()[start - 1:end]
    (d / "source.cc").write_text(
        f"// {uid} – {u['name']}\n// Trích từ {u['file']}, dòng {start}–{end} (chỉ để xem, không compile)\n\n"
        + "\n".join(src) + "\n", encoding="utf-8")
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
