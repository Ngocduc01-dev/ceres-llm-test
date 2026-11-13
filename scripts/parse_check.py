#!/usr/bin/env python3
"""Phase 0 – parse thử toàn bộ source Ceres bằng libclang.

Mục đích: chứng minh Phase 1/2 (code graph, liệt kê unit) làm được, tức là
libclang đọc được mọi file .cc với đúng cờ compile lấy từ compile_commands.json.

Đầu ra:
  reports/parse/parse_report.json  – kết quả từng file (lỗi, danh sách unit)
  reports/parse/summary.txt        – tóm tắt
Chạy trong container (run_docker.sh), sau build.sh.
"""
import json
import os
import sys
import time
from collections import Counter
from pathlib import Path

import clang.cindex as ci

REPO = Path(os.environ.get("REPO_DIR", Path(__file__).resolve().parents[1]))
SRC = Path(os.environ.get("SRC_DIR", REPO / "ceres-solver"))
DB_DIR = REPO / "data"
OUT = REPO / "reports" / "parse"

ci.Config.set_library_file(os.environ.get("LIBCLANG_PATH", "/usr/lib/llvm-18/lib/libclang.so"))

FUNC_KINDS = {
    ci.CursorKind.FUNCTION_DECL, ci.CursorKind.CXX_METHOD,
    ci.CursorKind.CONSTRUCTOR, ci.CursorKind.DESTRUCTOR,
    ci.CursorKind.FUNCTION_TEMPLATE, ci.CursorKind.CONVERSION_FUNCTION,
}
FUNC_KIND_IDS = {k.value for k in FUNC_KINDS}


def in_scope(path: str) -> bool:
    """Unit thuộc phạm vi: code Ceres, không phải test, không phải code sinh tự động."""
    p = path.replace("\\", "/")
    if "/internal/ceres/" not in p and "/include/ceres/" not in p:
        return False
    if p.endswith("_test.cc") or "/generated/" in p or "test_util" in p or "gmock" in p:
        return False
    return True


def clean_args(cmd):
    """Bỏ tên compiler, file nguồn, -o/-c và cờ chỉ GCC hiểu; giữ -I, -D, -std..."""
    args = list(cmd.arguments)[1:]
    out, skip = [], False
    for a in args:
        if skip:
            skip = False
            continue
        if a in ("-o", "-c", "-MF", "-MT", "-MQ"):
            skip = a != "-c"
            continue
        if a == cmd.filename or a.endswith(os.path.basename(cmd.filename)):
            continue
        if a.startswith("--coverage") or a.startswith("-fprofile") or a.startswith("-ftest-coverage"):
            continue
        out.append(a)
    return out


def is_ceres_file(path: str) -> bool:
    """File của Ceres. Bỏ googletest/gmock mà Ceres 2.2.0 để sẵn trong internal/ceres/."""
    p = path.replace("\\", "/")
    if "/gmock" in p or "/gtest" in p:
        return False
    return "/internal/ceres/" in p or "/include/ceres/" in p


def collect_units(cursor, found):
    """Duyệt AST có cắt tỉa: chỉ đi vào node nằm trong file của Ceres.

    Bỏ qua toàn bộ cây con của Eigen, abseil, thư viện chuẩn (chiếm >90% AST)
    và không đi vào thân hàm. Nhờ vậy nhanh hơn hàng chục lần so với walk_preorder().
    """
    for child in cursor.get_children():
        f = child.location.file
        if f is None or not is_ceres_file(f.name):
            continue
        # So sánh bằng id số: binding Python không có tên cho mọi loại node
        # libclang trả về (vd. kind 280), gọi child.kind sẽ ném ValueError.
        if child._kind_id in FUNC_KIND_IDS:
            if child.is_definition() and in_scope(f.name):
                found.append((f.name, child.extent.start.line, child.extent.end.line,
                              child.spelling, ci.CursorKind.from_id(child._kind_id).name))
            continue  # không đi vào thân hàm
        collect_units(child, found)


def parse_one(job):
    """Chạy trong process con: parse 1 file, trả về lỗi + danh sách unit."""
    filename, args = job
    index = ci.Index.create()
    rel = os.path.relpath(filename, SRC)
    t = time.time()
    try:
        tu = index.parse(filename, args=args, options=0)
    except ci.TranslationUnitLoadError as e:
        return {"file": rel, "ok": False, "fatal": str(e), "errors": [], "n_errors": 1}, []
    errors = [f"{d.location.file}:{d.location.line}: {d.spelling}"
              for d in tu.diagnostics if d.severity >= ci.Diagnostic.Error]
    found = []
    collect_units(tu.cursor, found)
    return {"file": rel, "ok": not errors, "errors": errors[:10],
            "n_errors": len(errors), "seconds": round(time.time() - t, 1)}, found


def main():
    from multiprocessing import Pool
    db = ci.CompilationDatabase.fromDirectory(str(DB_DIR))
    jobs = sorted((c.filename, clean_args(c)) for c in db.getAllCompileCommands()
                  if c.filename.endswith(".cc") and is_ceres_file(c.filename))
    OUT.mkdir(parents=True, exist_ok=True)

    files, units = [], {}
    t0 = time.time()
    with Pool(int(os.environ.get("JOBS", os.cpu_count() or 4))) as pool:
        for i, (info, found) in enumerate(pool.imap_unordered(parse_one, jobs), 1):
            n_new = 0
            for fname, line, end, name, kind in found:
                key = (os.path.relpath(fname, SRC), line, name)
                if key not in units:
                    units[key] = {"file": key[0], "line": line, "end_line": end,
                                  "name": name, "kind": kind}
                    n_new += 1
            info["new_units"] = n_new
            files.append(info)
            print(f"[{i}/{len(jobs)}] {info['file']}: {info['n_errors']} lỗi, +{n_new} unit", flush=True)
    files.sort(key=lambda f: f["file"])

    ok = sum(f["ok"] for f in files)
    kinds = Counter(u["kind"] for u in units.values())
    in_headers = sum(1 for u in units.values() if u["file"].endswith(".h"))
    in_test_files = sum(1 for f in files if f["file"].endswith("_test.cc"))
    summary = [
        f"Số file .cc trong internal/ceres có trong compile_commands: {len(files)}",
        f"  trong đó file test có sẵn (*_test.cc): {in_test_files}",
        f"Parse không lỗi: {ok}/{len(files)}",
        f"Parse có lỗi:    {len(files) - ok}",
        f"Số unit (hàm/method có thân, trong phạm vi, không trùng): {len(units)}",
        f"  nằm trong header (.h): {in_headers}",
        f"  theo loại: {dict(kinds)}",
        f"Thời gian: {time.time() - t0:.0f}s",
    ]
    (OUT / "summary.txt").write_text("\n".join(summary) + "\n", encoding="utf-8")
    (OUT / "parse_report.json").write_text(
        json.dumps({"files": files, "units": sorted(units.values(), key=lambda u: (u["file"], u["line"]))},
                   ensure_ascii=False, indent=1), encoding="utf-8")
    print("\n".join(summary))
    return 0 if ok == len(files) else 1


if __name__ == "__main__":
    sys.exit(main())
