#!/usr/bin/env python3
"""So sánh 2 báo cáo độ phủ (file --json-summary của gcovr), in ra bảng markdown.

  python3 scripts/compare_baseline.py A/summary.json B/summary.json --names "Lần 1" "Lần 2"
"""
import argparse
import json


def load(p):
    d = json.load(open(p, encoding="utf-8"))
    return d, {f["filename"]: f for f in d["files"]}


def pct(a, b):
    return f"{100 * a / b:.1f}%" if b else "-"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("a")
    ap.add_argument("b")
    ap.add_argument("--names", nargs=2, default=["A", "B"])
    ap.add_argument("--top", type=int, default=12)
    x = ap.parse_args()
    (da, fa), (db, fb) = load(x.a), load(x.b)
    A, B = x.names
    out = [f"| | {A} | {B} |", "|---|---|---|", f"| Số file | {len(fa)} | {len(fb)} |"]
    for k, lab in (("line", "Dòng (C1)"), ("branch", "Nhánh (C2)"), ("function", "Hàm")):
        out.append(f"| {lab} | {da[k + '_covered']} / {da[k + '_total']} = **{pct(da[k + '_covered'], da[k + '_total'])}** "
                   f"| {db[k + '_covered']} / {db[k + '_total']} = **{pct(db[k + '_covered'], db[k + '_total'])}** |")
    s = lambda fs, d, k: sum(d[f][k] for f in fs)
    for name, only, d in ((A, sorted(set(fa) - set(fb)), fa), (B, sorted(set(fb) - set(fa)), fb)):
        out += ["", f"**File chỉ có ở {name}: {len(only)}** – {s(only, d, 'line_total')} dòng, "
                    f"{s(only, d, 'branch_total')} nhánh, {s(only, d, 'function_total')} hàm", ""]
        if only:
            out += ["| File | Dòng | Nhánh (phủ/tổng) | Hàm |", "|---|---|---|---|"]
            for f in sorted(only, key=lambda f: -d[f]["branch_total"])[:x.top]:
                out.append(f"| `{f}` | {d[f]['line_total']} | {d[f]['branch_covered']}/{d[f]['branch_total']} | {d[f]['function_total']} |")
    common = set(fa) & set(fb)
    out += ["", f"**{len(common)} file chung:**", "", f"| | {A} | {B} |", "|---|---|---|"]
    for k, lab in (("line", "Dòng"), ("branch", "Nhánh"), ("function", "Hàm")):
        ca, ta, cb, tb = s(common, fa, k + "_covered"), s(common, fa, k + "_total"), s(common, fb, k + "_covered"), s(common, fb, k + "_total")
        out.append(f"| {lab} | {ca} / {ta} = {pct(ca, ta)} | {cb} / {tb} = {pct(cb, tb)} |")
    out += ["", "**File chung lệch tổng số nhánh nhiều nhất:**", "",
            f"| File | Nhánh {A} | Nhánh {B} | Hàm {A} | Hàm {B} |", "|---|---|---|---|---|"]
    for f in sorted(common, key=lambda f: -abs(fa[f]["branch_total"] - fb[f]["branch_total"]))[:x.top]:
        out.append(f"| `{f}` | {fa[f]['branch_covered']}/{fa[f]['branch_total']} | {fb[f]['branch_covered']}/{fb[f]['branch_total']} "
                   f"| {fa[f]['function_total']} | {fb[f]['function_total']} |")
    out += ["", "**File chung lệch số nhánh được phủ nhiều nhất (cùng tổng thì lệch do test chạy khác):**", "",
            f"| File | Nhánh {A} | Nhánh {B} |", "|---|---|---|"]
    for f in sorted(common, key=lambda f: -abs(fa[f]["branch_covered"] - fb[f]["branch_covered"]))[:x.top]:
        out.append(f"| `{f}` | {fa[f]['branch_covered']}/{fa[f]['branch_total']} | {fb[f]['branch_covered']}/{fb[f]['branch_total']} |")
    print("\n".join(out))


if __name__ == "__main__":
    main()
