#!/usr/bin/env bash
# Chạy một lệnh bên trong container.
# Ví dụ:  scripts/run_docker.sh bash scripts/build.sh
#
# Mount:
#   repo (gốc)            -> /work/repo           (script, report, log)
#   repo/ceres-solver     -> /work/ceres-solver   (source Ceres)
#   volume build          -> /work/build-cov      (thư mục build)
#   volume ccache         -> /work/.ccache
#
# Vì sao build nằm trong Docker volume, KHÔNG nằm trên ổ đĩa của máy:
#   ghi hàng nghìn file .o/.gcno qua bind mount Windows -> Linux rất chậm.
# Vì sao Ceres mount riêng vào /work/ceres-solver:
#   đường dẫn source cố định -> compile_commands.json, ccache, dữ liệu gcov
#   không phụ thuộc repo được clone ở đâu trên máy.
set -euo pipefail
IMAGE=${IMAGE:-ceres-testgen:phase0}
REPO="$(cd "$(dirname "$0")/.." && pwd)"
# Lấy version Ceres TRƯỚC khi tắt chuyển đổi đường dẫn (git.exe trên Windows cần đường dẫn đã chuyển)
CERES_VERSION="$(git -C "$REPO/ceres-solver" describe --tags 2>/dev/null || echo unknown)"

# Git Bash trên Windows tự đổi đường dẫn /work/... -> C:/Program Files/Git/work/...
export MSYS_NO_PATHCONV=1

docker run --rm -t \
  -v "$REPO:/work/repo" \
  -v "$REPO/ceres-solver:/work/ceres-solver" \
  -v "${BUILD_VOLUME:-ceres-testgen-build-2.2.0}:/work/build-cov" \
  -v ceres-testgen-ccache:/work/.ccache \
  -e REPO_DIR=/work/repo \
  -e SRC_DIR=/work/ceres-solver \
  -e CERES_VERSION="$CERES_VERSION" \
  -w /work/repo \
  "$IMAGE" "$@"
