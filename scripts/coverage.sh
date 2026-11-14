#!/usr/bin/env bash
# Chạy toàn bộ test có sẵn của Ceres rồi đo độ phủ (baseline).
# Chạy trong container (run_docker.sh) hoặc trực tiếp trên Linux/WSL, sau build.sh.
set -euo pipefail

REPO=${REPO_DIR:-$(cd "$(dirname "$0")/.." && pwd)}
SRC=${SRC_DIR:-$REPO/ceres-solver}
if [ -d /work/build-cov ]; then DEFAULT_BUILD=/work/build-cov; else DEFAULT_BUILD=$HOME/ceres-build-cov; fi
BUILD=${BUILD_DIR:-$DEFAULT_BUILD}
OUT=${OUT_DIR:-$REPO/reports/baseline}
JOBS=${JOBS:-$(nproc)}
mkdir -p "$OUT/html"

# Timeout cho mỗi test (giây). Test bundle adjustment ở Debug + coverage atomic chạy 15–25 phút.
# Test bị timeout bị kill -> gcov KHÔNG ghi được dữ liệu của nó -> độ phủ bị thấp.
TEST_TIMEOUT=${TEST_TIMEOUT:-3600}

if [ "${RERUN_FAILED:-0}" = "1" ]; then
  # Chỉ chạy lại test fail/timeout ở lần trước. GIỮ .gcda cũ -> độ phủ cộng dồn.
  (cd "$BUILD" && ctest --rerun-failed -j "$JOBS" --timeout "$TEST_TIMEOUT" --output-on-failure \
      > "$OUT/ctest_rerun.log" 2>&1) || true
  tail -n 5 "$OUT/ctest_rerun.log"
elif [ "${SKIP_TESTS:-0}" != "1" ]; then
  # SKIP_TESTS=1: chỉ xuất lại báo cáo từ dữ liệu .gcda đã có, không chạy lại test
  # 1. Xoá dữ liệu độ phủ cũ (.gcda) để số liệu chỉ phản ánh lần chạy này
  find "$BUILD" -name '*.gcda' -delete

  # 2. Chạy test. Không dừng khi có test FAIL: bài toán không quan tâm PASS/FAIL,
  #    chỉ cần code được thực thi để đo độ phủ.
  (cd "$BUILD" && ctest -j "$JOBS" --timeout "$TEST_TIMEOUT" --output-on-failure \
      > "$OUT/ctest.log" 2>&1) || true
  tail -n 5 "$OUT/ctest.log"
fi

# 3. Đo độ phủ. Chỉ tính code của Ceres (internal/ceres, include/ceres),
#    bỏ test, code sinh tự động, abseil, googletest.
gcovr --root "$SRC" --object-directory "$BUILD" \
  --gcov-executable gcov \
  --filter "$SRC/internal/ceres/" --filter "$SRC/include/ceres/" \
  --exclude '.*_test\.cc$' --exclude '.*/generated/.*' \
  --exclude '.*test_util.*' --exclude '.*/gmock.*' --exclude '.*/gtest/.*' \
  --exclude-throw-branches --exclude-unreachable-branches \
  --gcov-ignore-parse-errors=negative_hits.warn_once_per_file \
  --gcov-exclude-directories '.*/CMakeFiles/[0-9.]+/.*' \
  -j "$JOBS" \
  --txt "$OUT/summary.txt" \
  --json "$OUT/coverage.json" \
  --json-summary "$OUT/summary.json" \
  --html-details "$OUT/html/index.html" \
  --print-summary | tee "$OUT/print_summary.txt"

# 4. Trang HTML tổng quan gọn (1 file, commit được) – đọc lại từ coverage.json, không gọi gcov lại.
#    Bản chi tiết từng dòng (html/, ~20 MB) không commit.
gcovr --root "$SRC" --add-tracefile "$OUT/coverage.json" \
  --html "$OUT/index.html" --html-title "Ceres ${CERES_VERSION:-?} – baseline coverage" \
  >/dev/null

echo "COVERAGE OK -> $OUT"
