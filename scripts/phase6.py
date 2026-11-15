#!/usr/bin/env python3
"""Phase 6 (lượt 1) – compile, chạy, đo phủ từng unit. Chưa sửa lỗi, chỉ ghi lại.

Với mỗi unit có units/<id>/<id>_test.cc:
  1. Compile test (cùng cờ với test có sẵn của Ceres, bật --coverage) + scripts/phase6_main.cc,
     link với thư viện Ceres bản coverage trong /work/build-cov.
  2. Chạy TỪNG test (--gtest_filter), timeout 10 giây/test. PASS/FAIL/crash đều chấp nhận, chỉ ghi lại.
     Dữ liệu gcov của mỗi unit ghi riêng vào thư mục của unit (GCOV_PREFIX) -> chạy song song được.
  3. gcovr --decisions đo phủ, chỉ lấy các dòng của unit:
       C1 = số dòng code của unit đã chạy / tổng số dòng code
       C2 = số nhánh đã đi / tổng số nhánh, đếm theo ĐIỂM RẼ NHÁNH như CFG Phase 4:
            if / for / while (cả "a && b") = 1 điểm, 2 nhánh (đúng, sai); switch: mỗi case = 1 nhánh.
            Không tính dòng CHECK/DCHECK/LOG(FATAL). Điểm gcovr không xác định được -> "uncheckable", ghi riêng.

Đầu ra:
  units/<id>/result.json     – trạng thái, kết quả từng test, C1, C2, nhánh chưa phủ
  units/<id>/coverage.json   – số liệu gcovr (định dạng JSON của gcovr), chỉ các dòng của unit
  units/<id>/compile.log     – log lỗi compile/link (chỉ khi lỗi)
  reports/phase6/summary.md, summary.csv     – bảng tổng hợp mọi unit đã chạy Phase 6
  reports/phase6/gen_coverage.html           – trang tổng quan độ phủ (giống reports/baseline/index.html)
  reports/phase6/html/                       – trang chi tiết từng file (không commit)

Chạy trong Docker (cần build Ceres bản coverage ở /work/build-cov – scripts/build.sh):
  MSYS_NO_PATHCONV=1 scripts/run_docker.sh python3 scripts/phase6.py --smoke
  MSYS_NO_PATHCONV=1 scripts/run_docker.sh python3 scripts/phase6.py            # mọi unit đã có file test
  MSYS_NO_PATHCONV=1 scripts/run_docker.sh python3 scripts/phase6.py --ids u0540 u0541 -j 4
  MSYS_NO_PATHCONV=1 scripts/run_docker.sh python3 scripts/phase6.py --report-only   # chỉ dựng lại báo cáo
"""
import argparse
import csv
import json
import os
import re
import shutil
import subprocess
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

REPO = Path(os.environ.get("REPO_DIR", Path(__file__).resolve().parents[1]))
SRC = Path(os.environ.get("SRC_DIR", REPO / "ceres-solver"))
BUILD = Path(os.environ.get("BUILD_DIR", "/work/build-cov"))
WORK = BUILD / "gen"          # thư mục làm việc trong Docker volume (nhanh hơn ổ Windows)
REPORT = REPO / "reports" / "phase6"
TEST_TIMEOUT = 10
COMPILE_TIMEOUT = 600
KEEP = False

CXXFLAGS = [
    "-DGFLAGS_IS_A_DLL=0", "-DGLOG_CUSTOM_PREFIX_SUPPORT",
    f"-I{SRC}/internal/ceres", f"-I{SRC}/internal", f"-I{SRC}/include", f"-I{BUILD}/include",
    "-isystem", "/usr/include/eigen3",
    "--coverage", "-fprofile-update=atomic", "-O0", "-g", "-std=c++17",
    "-Wno-unknown-pragmas", "-Wno-sign-compare", "-Wno-unused-parameter", "-Wno-missing-field-initializers",
    "-fPIE",
]
LIBS = [f"{BUILD}/lib/libgtest-debug.a", f"{BUILD}/lib/libtest_util-debug.a", f"{BUILD}/lib/libceres-debug.a",
        f"{BUILD}/lib/libgtest-debug.a", f"{BUILD}/lib/libceres-debug.a",
        "-lglog", "-lgflags", "-lpthread"]
CHECK_LINE = r"\s*(D?CHECK(_[A-Z]+)?|LOG\(FATAL\)|D?CHECK_NOTNULL)\b"
RUN_KINDS = ("pass", "fail", "check_fail", "crash", "timeout")


def sh(cmd, timeout, env=None, cwd=None):
    try:
        p = subprocess.run(cmd, capture_output=True, text=True, timeout=timeout, env=env, cwd=cwd, errors="replace")
        return p.returncode, p.stdout + p.stderr
    except subprocess.TimeoutExpired:
        return "timeout", "[timeout]"


def build_main():
    """Compile phase6_main.cc 1 lần."""
    WORK.mkdir(parents=True, exist_ok=True)
    obj = WORK / "phase6_main.o"
    src = REPO / "scripts" / "phase6_main.cc"
    if not obj.exists() or obj.stat().st_mtime < src.stat().st_mtime:
        code, out = sh(["g++", *[f for f in CXXFLAGS if f != "--coverage"], "-c", str(src), "-o", str(obj)], COMPILE_TIMEOUT)
        if code != 0:
            raise SystemExit(f"Không compile được phase6_main.cc:\n{out}")
    return obj


def compile_errors(log):
    """Các dòng 'error:' đầu tiên, bỏ đường dẫn dài."""
    errs = []
    for line in log.splitlines():
        if " error: " in line or line.startswith("/usr/bin/ld:") or "undefined reference" in line:
            errs.append(re.sub(r"^/work/(repo|ceres-solver|build-cov)/", "", line.strip())[:300])
        if len(errs) >= 8:
            break
    return errs


def list_tests(binary):
    _, out = sh([str(binary), "--gtest_list_tests"], 30)
    tests, suite = [], None
    for line in out.splitlines():
        if not line.strip():
            continue
        if not line.startswith(" "):
            suite = line.split("#")[0].strip()
        elif suite:
            tests.append(suite + line.split("#")[0].strip())
    return tests


def outcome(code):
    if code == 0:
        return "pass"
    if code == 1:
        return "fail"
    if code in ("timeout", 124, 143):
        return "timeout"
    if code == 134:
        return "check_fail"
    return "crash"


def check_lines(src, start, end):
    """Các dòng thuộc lệnh CHECK/DCHECK/LOG(FATAL) (kể cả phần '<< ...' viết tiếp ở dòng sau, đến dấu ';')."""
    out, inside = set(), False
    for n in range(start, end + 1):
        code = src[n - 1].split("//")[0]
        if re.match(CHECK_LINE, code):
            inside = True
        if inside:
            out.add(n)
            if code.rstrip().endswith(";"):
                inside = False
    return out


def count(lines):
    """C1, C2 (theo điểm rẽ nhánh) và danh sách nhánh chưa phủ từ các dòng gcovr (đã lọc theo unit)."""
    c1 = {"covered": sum(1 for ln in lines if ln["count"] > 0), "total": len(lines)}
    c2 = {"covered": 0, "total": 0, "uncheckable": 0}
    missing = []
    for ln in lines:
        d = ln.get("gcovr/decision")
        if not d:
            continue
        miss = []
        if d["type"] == "conditional":
            c2["total"] += 2
            c2["covered"] += (d["count_true"] > 0) + (d["count_false"] > 0)
            miss = [k for k, key in (("đúng", "count_true"), ("sai", "count_false")) if d[key] == 0]
        elif d["type"] == "switch":
            c2["total"] += 1
            c2["covered"] += d["count"] > 0
            miss = ["case"] if d["count"] == 0 else []
        else:
            c2["uncheckable"] += 1
        if miss:
            missing.append({"line": ln["line_number"], "missing": miss})
    return c1, c2, missing


def coverage(u, gcda_dir):
    """Ghép .gcno cạnh .gcda, gọi gcovr --decisions, giữ lại các dòng của unit."""
    for gcda in gcda_dir.rglob("*.gcda"):
        gcno = Path(str(gcda)[len(str(gcda_dir)):]).with_suffix(".gcno")
        if gcno.exists():
            shutil.copy(gcno, gcda.with_suffix(".gcno"))
    out_json = gcda_dir / "cov.json"
    code, log = sh(["gcovr", "--root", str(SRC), "--object-directory", str(gcda_dir), str(gcda_dir),
                    "--gcov-executable", "gcov", "--filter", str(SRC / u["file"]), "--decisions",
                    "--gcov-ignore-parse-errors=negative_hits.warn_once_per_file",
                    "--json", str(out_json)], 300)
    if code != 0 or not out_json.exists():
        return None, log[-1500:]
    start, end = u["lines"]
    src = (SRC / u["file"]).read_text(errors="replace").splitlines()
    checks = check_lines(src, start, end)
    data = json.loads(out_json.read_text())
    merged = {}
    for f in data.get("files", []):
        for ln in f["lines"]:
            n = ln["line_number"]
            if not (start <= n <= end) or ln.get("gcovr/noncode"):
                continue
            br = [b["count"] for b in ln.get("branches", []) if not b.get("throw")]
            ln = {"line_number": n, "count": ln["count"], "branches": [], "_br": br,
                  **({"gcovr/decision": ln["gcovr/decision"]} if ln.get("gcovr/decision") and n not in checks else {})}
            prev = merged.get(n)
            if prev:  # cùng dòng ở nhiều object (hàm inline trong header) -> cộng dồn
                add_line(prev, ln)
                if len(prev["_br"]) == len(br):
                    prev["_br"] = [x + y for x, y in zip(prev["_br"], br)]
            else:
                merged[n] = ln
    lines = [merged[n] for n in sorted(merged)]
    infer_decisions(lines, src, checks)
    c1, c2, missing = count(lines)
    c2["inferred"] = sum(1 for ln in lines if ln.get("_inf"))  # số điểm rẽ nhánh phải tự suy ra
    for ln in lines:
        ln.pop("_br", None)
        ln.pop("_inf", None)
    for m in missing:
        m["code"] = src[m["line"] - 1].strip()[:120]
    cov_file = {"gcovr/format_version": data.get("gcovr/format_version"),
                "files": [{"file": u["file"], "lines": lines, "functions": []}]}
    return {"c1": c1, "c2": c2, "uncovered": missing, "_coverage": cov_file}, None


IF_LINE = re.compile(r"^\s*(\}\s*else\s+)?(if|while)\s*\(.*\)\s*\{\s*$")
TERNARY = re.compile(r"\?[^:?]*:")


def infer_decisions(lines, src, checks):
    """Bù các điểm rẽ nhánh gcovr --decisions không nhận ra (vẫn đếm theo điểm rẽ nhánh, 2 nhánh/điểm):
      - "if (...) {" mà gcov gắn nhánh sang dòng khác (thường là dòng "}" ở -O0):
          nhánh đúng = số lần chạy dòng code đầu tiên trong thân, nhánh sai = số lần chạy dòng if - nhánh đúng
      - toán tử "?:" trên 1 dòng có đúng 2 nhánh gcov: mỗi nhánh gcov = 1 nhánh của điểm rẽ nhánh."""
    by_line = {ln["line_number"]: ln for ln in lines}
    for ln in lines:
        n = ln["line_number"]
        if ln.get("gcovr/decision") or n in checks:
            continue
        code = src[n - 1].split("//")[0]
        if IF_LINE.match(code) and not ln["_br"]:
            body = next((by_line[k] for k in range(n + 1, n + 30) if k in by_line), None)
            if body is not None:
                t = body["count"] if body["count"] <= ln["count"] else ln["count"]
                ln["gcovr/decision"] = {"type": "conditional", "count_true": t, "count_false": ln["count"] - t}
                ln["_inf"] = True
        elif TERNARY.search(code) and len(ln["_br"]) == 2:
            ln["gcovr/decision"] = {"type": "conditional", "count_true": ln["_br"][0], "count_false": ln["_br"][1]}
            ln["_inf"] = True


def add_line(a, b):
    """Cộng số liệu dòng b vào dòng a (cùng số dòng)."""
    a["count"] += b["count"]
    da, db = a.get("gcovr/decision"), b.get("gcovr/decision")
    if db and not da:
        a["gcovr/decision"] = dict(db)
    elif da and db and da["type"] == db["type"]:
        for k in ("count_true", "count_false", "count"):
            if k in da:
                da[k] += db[k]


def run_unit(u, main_obj):
    uid = u["id"]
    d = REPO / "units" / uid
    test_src = d / f"{uid}_test.cc"
    info = json.loads((d / "info.json").read_text(encoding="utf-8")) if (d / "info.json").exists() else {}
    res = {"id": uid, "name": u["name"], "status": None,
           "cfg_branches": (info.get("cfg") or {}).get("branches")}
    for f in ("compile.log", "coverage.json"):
        (d / f).unlink(missing_ok=True)
    if not test_src.exists():
        res["status"] = "no_test_file"
        return res
    w = WORK / uid
    shutil.rmtree(w, ignore_errors=True)
    w.mkdir(parents=True)
    obj, binary = w / "test.o", w / "test"
    code, log = sh(["g++", *CXXFLAGS, "-c", str(test_src), "-o", str(obj)], COMPILE_TIMEOUT)
    stage = "compile_fail"
    if code == 0:
        code, log = sh(["g++", "--coverage", str(obj), str(main_obj), "-o", str(binary), *LIBS], COMPILE_TIMEOUT)
        stage = "link_fail"
    if code != 0:
        res["status"] = stage
        res["errors"] = compile_errors(log) or [str(code)]
        (d / "compile.log").write_text("\n".join(log.splitlines()[:300]) + "\n", encoding="utf-8")
        return res
    tests = list_tests(binary)
    if not tests:
        res["status"] = "no_tests"
        return res
    gcda = w / "gcda"
    env = dict(os.environ, GCOV_PREFIX=str(gcda), GCOV_PREFIX_STRIP="0")
    runs = {}
    for t in tests:
        code, _ = sh(["timeout", "-s", "TERM", str(TEST_TIMEOUT), str(binary), f"--gtest_filter={t}"],
                     TEST_TIMEOUT + 5, env=env, cwd=w)
        runs[t] = outcome(code)
    res["tests"] = runs
    res["run"] = {k: sum(1 for v in runs.values() if v == k) for k in RUN_KINDS}
    cov, err = coverage(u, gcda)
    if cov is None:
        res["status"] = "coverage_fail"
        res["errors"] = [err]
        return res
    (d / "coverage.json").write_text(json.dumps(cov.pop("_coverage")) + "\n", encoding="utf-8")
    res.update(cov)
    res["status"] = "ok"
    if not KEEP:
        shutil.rmtree(w, ignore_errors=True)  # giữ volume gọn
    return res


def pct(c):
    return f"{100 * c['covered'] / c['total']:.0f}%" if c and c.get("total") else "–"


def main():
    global KEEP
    ap = argparse.ArgumentParser()
    ap.add_argument("--smoke", action="store_true")
    ap.add_argument("--ids", nargs="*")
    ap.add_argument("-j", type=int, default=4, help="số unit chạy song song (RAM ~1 GB/unit khi compile)")
    ap.add_argument("--keep", action="store_true", help="giữ thư mục build/gcda của unit (để soát lỗi)")
    ap.add_argument("--report-only", action="store_true", help="không chạy, chỉ dựng lại báo cáo từ result.json")
    ap.add_argument("--first", type=int, help="báo cáo chỉ tính N unit đầu theo thứ tự sinh test")
    a = ap.parse_args()
    KEEP = a.keep
    units = json.loads((REPO / "data" / "units.json").read_text(encoding="utf-8"))
    if not a.report_only:
        todo = units
        if a.smoke:
            ids = {l.split()[0] for l in (REPO / "data" / "smoke_test_units.txt").read_text().splitlines() if l.strip()}
            todo = [u for u in units if u["id"] in ids]
        elif a.ids:
            todo = [u for u in units if u["id"] in set(a.ids)]
        todo = [u for u in todo if (REPO / "units" / u["id"] / f"{u['id']}_test.cc").exists()]
        main_obj = build_main()
        print(f"Phase 6: {len(todo)} unit, {a.j} song song")

        def job(u):
            r = run_unit(u, main_obj)
            (REPO / "units" / u["id"] / "result.json").write_text(
                json.dumps(r, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
            print(f"  {u['id']} {r['status']:<13} C1 {pct(r.get('c1')):>4}  C2 {pct(r.get('c2')):>4}"
                  + (f"  {r['errors'][0][:110]}" if r.get("errors") else ""), flush=True)

        with ThreadPoolExecutor(a.j) as ex:
            list(ex.map(job, todo))
    # báo cáo gộp mọi unit đã có result.json (không chỉ lần chạy này);
    # --first N: chỉ tính N unit đầu theo thứ tự sinh test (topo_level, order)
    scope = units
    if a.first:
        scope = sorted(units, key=lambda u: (u["topo_level"], u["order"]))[:a.first]
    results = [json.loads(p.read_text(encoding="utf-8"))
               for u in scope if (p := REPO / "units" / u["id"] / "result.json").exists()]
    write_summary(results)
    write_html(results)


def write_summary(results):
    REPORT.mkdir(parents=True, exist_ok=True)
    with open(REPORT / "summary.csv", "w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow(["id", "name", "status", "tests", *RUN_KINDS,
                    "c1_covered", "c1_total", "c2_covered", "c2_total", "c2_uncheckable", "cfg_branches", "first_error"])
        for r in results:
            run = r.get("run") or {}
            c1, c2 = r.get("c1") or {}, r.get("c2") or {}
            w.writerow([r["id"], r["name"], r["status"], len(r.get("tests") or {}),
                        *[run.get(k, "") for k in RUN_KINDS],
                        c1.get("covered", ""), c1.get("total", ""), c2.get("covered", ""), c2.get("total", ""),
                        c2.get("uncheckable", ""), r.get("cfg_branches", ""), (r.get("errors") or [""])[0]])
    by = {}
    for r in results:
        by[r["status"]] = by.get(r["status"], 0) + 1
    ok = [r for r in results if r["status"] == "ok"]
    tot = lambda k, f: sum((r.get(k) or {}).get(f, 0) for r in ok)
    runs = {k: sum((r.get("run") or {}).get(k, 0) for r in ok) for k in RUN_KINDS}
    with_br = [r for r in ok if r["c2"]["total"]]
    full = sum(1 for r in with_br if r["c2"]["covered"] == r["c2"]["total"])
    match = sum(1 for r in with_br if r["c2"]["total"] == r.get("cfg_branches"))
    md = [f"# Phase 6 – lượt 1: compile, chạy, đo phủ", "",
          "Trang tổng quan độ phủ: [gen_coverage.html](gen_coverage.html). Cách đo: `docs/phase6-guide.md`.", "",
          "| Trạng thái | Số unit |", "|---|---|"]
    md += [f"| `{k}` | {v} |" for k, v in sorted(by.items(), key=lambda x: -x[1])]
    md += ["", f"**Test case** (trong {len(ok)} unit chạy được): " + ", ".join(f"{k} {v}" for k, v in runs.items()), "",
           "**Độ phủ trên các dòng của unit** (gộp các unit chạy được):", "",
           f"- C1 (dòng): {tot('c1', 'covered')}/{tot('c1', 'total')}"
           f" = {pct({'covered': tot('c1', 'covered'), 'total': tot('c1', 'total')})}",
           f"- C2 (nhánh, đếm theo điểm rẽ nhánh như CFG): {tot('c2', 'covered')}/{tot('c2', 'total')}"
           f" = {pct({'covered': tot('c2', 'covered'), 'total': tot('c2', 'total')})}"
           f"; điểm rẽ nhánh không đo được (uncheckable): {tot('c2', 'uncheckable')}",
           f"- Unit có nhánh: {len(with_br)}; phủ đủ 100% nhánh: {full}; "
           f"tổng nhánh đo được khớp số nhánh CFG: {match}/{len(with_br)}", "",
           "| Unit | Trạng thái | Test (pass/tổng) | C1 | C2 | Nhánh CFG | Nhánh chưa phủ / lỗi đầu tiên |",
           "|---|---|---|---|---|---|---|"]
    for r in results:
        run, c2 = r.get("run") or {}, r.get("c2")
        note = "; ".join(f"dòng {m['line']}: {'/'.join(m['missing'])}" for m in r.get("uncovered") or [])
        note = note or (r.get("errors") or [""])[0][:120]
        md.append(f"| {r['id']} | {r['status']} | {run.get('pass', '')}/{len(r.get('tests') or {})} | {pct(r.get('c1'))} | "
                  + (f"{c2['covered']}/{c2['total']}" if c2 and c2["total"] else "–")
                  + f" | {r.get('cfg_branches') if r.get('cfg_branches') is not None else ''} | "
                  + note.replace("|", "\\|") + " |")
    (REPORT / "summary.md").write_text("\n".join(md) + "\n", encoding="utf-8")


def write_html(results):
    """Gộp coverage.json của các unit (theo file, theo dòng) -> trang HTML của gcovr như baseline."""
    files, version = {}, None
    for r in results:
        p = REPO / "units" / r["id"] / "coverage.json"
        if r["status"] != "ok" or not p.exists():
            continue
        data = json.loads(p.read_text(encoding="utf-8"))
        version = version or data.get("gcovr/format_version")
        for f in data["files"]:
            lines = files.setdefault(f["file"], {})
            for ln in f["lines"]:
                if ln["line_number"] in lines:
                    add_line(lines[ln["line_number"]], ln)
                else:
                    lines[ln["line_number"]] = json.loads(json.dumps(ln))
    if not files:
        return
    def as_branches(ln):
        # chỉ 1 loại nhánh: mỗi điểm rẽ nhánh -> 2 nhánh (đúng, sai), mỗi case -> 1 nhánh; gcovr hiện ở cột "Branches"
        d = ln.get("gcovr/decision") or {}
        counts = ([d["count_true"], d["count_false"]] if d.get("type") == "conditional"
                  else [d["count"]] if d.get("type") == "switch" else [])
        return {"line_number": ln["line_number"], "count": ln["count"],
                "branches": [{"count": c, "fallthrough": False, "throw": False, "blockno": 0} for c in counts]}

    merged = REPORT / "gen_coverage.json"
    merged.write_text(json.dumps({"gcovr/format_version": version, "files": [
        {"file": f, "lines": [as_branches(v[n]) for n in sorted(v)], "functions": []}
        for f, v in sorted(files.items())]}), encoding="utf-8")
    (REPORT / "html").mkdir(exist_ok=True)
    ver = os.environ.get("CERES_VERSION", "")
    title = f"Ceres {ver if ver not in ('', 'unknown') else '2.2.0'} – độ phủ của test do LLM sinh"
    common = ["gcovr", "--root", str(SRC), "--add-tracefile", str(merged), "--html-title", title]
    for args in (["--html", str(REPORT / "gen_coverage.html")],
                 ["--html-details", str(REPORT / "html" / "gen_coverage.html")]):
        code, log = sh(common + args, 300)
        if code != 0:
            print(f"gcovr HTML lỗi:\n{log[-1500:]}")
    print(f"Báo cáo: {REPORT / 'summary.md'}, {REPORT / 'gen_coverage.html'} (chi tiết: {REPORT / 'html'})")


if __name__ == "__main__":
    main()
