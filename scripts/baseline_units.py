#!/usr/bin/env python3
"""Độ phủ của TEST CÓ SẴN của Ceres (baseline Phase 0) trên từng unit, cùng cách đếm với Phase 6.

Đọc .gcda còn lại trong /work/build-cov sau scripts/coverage.sh (175 test có sẵn), gọi gcovr --decisions 1 lần,
rồi tính C1 / C2 trên các dòng của từng unit bằng đúng hàm của scripts/phase6.py
(đếm theo điểm rẽ nhánh, bỏ dòng CHECK, tự suy ra if/?: mà gcovr không nhận ra).

Đầu ra: reports/phase6/baseline_units.csv  (id, c1_covered, c1_total, c2_covered, c2_total)
Chạy:   MSYS_NO_PATHCONV=1 scripts/run_docker.sh python3 scripts/baseline_units.py
"""
import csv
import json
import os
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import phase6  # noqa: E402

REPO, SRC, BUILD = phase6.REPO, phase6.SRC, phase6.BUILD
OUT = REPO / "reports" / "phase6"


def main():
    raw = Path("/tmp/baseline_decisions.json")
    if not raw.exists():
        subprocess.run(["gcovr", "--root", str(SRC), "--object-directory", str(BUILD), str(BUILD),
                        "--gcov-executable", "gcov", "--decisions", "-j", str(os.cpu_count() or 4),
                        "--filter", f"{SRC}/internal/ceres/", "--filter", f"{SRC}/include/ceres/",
                        "--exclude", r".*_test\.cc$", "--exclude", ".*/generated/.*",
                        "--gcov-exclude-directories", f"{BUILD}/gen/.*", "--gcov-exclude-directories", ".*/CMakeFiles/[0-9.]+/.*",
                        "--gcov-ignore-parse-errors=all",
                        "--json", str(raw)], check=True)
    files = {f["file"]: f["lines"] for f in json.loads(raw.read_text())["files"]}
    units = json.loads((REPO / "data" / "units.json").read_text(encoding="utf-8"))
    rows = []
    for u in units:
        start, end = u["lines"]
        src = (SRC / u["file"]).read_text(errors="replace").splitlines()
        checks = phase6.check_lines(src, start, end)
        lines = []
        for ln in files.get(u["file"], []):
            n = ln["line_number"]
            if start <= n <= end and not ln.get("gcovr/noncode"):
                d = ln.get("gcovr/decision") if n not in checks else None
                lines.append({"line_number": n, "count": ln["count"],
                              "_br": [b["count"] for b in ln.get("branches", []) if not b.get("throw")],
                              **({"gcovr/decision": dict(d)} if d else {})})
        phase6.infer_decisions(lines, src, checks)
        c1, c2, _ = phase6.count(lines)
        rows.append([u["id"], c1["covered"], c1["total"], c2["covered"], c2["total"]])
    with open(OUT / "baseline_units.csv", "w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow(["id", "c1_covered", "c1_total", "c2_covered", "c2_total"])
        w.writerows(rows)
    tot = [sum(r[i] for r in rows) for i in range(1, 5)]
    print(f"Baseline trên {len(rows)} unit: C1 {tot[0]}/{tot[1]}, C2 {tot[2]}/{tot[3]} -> {OUT / 'baseline_units.csv'}")


if __name__ == "__main__":
    main()
