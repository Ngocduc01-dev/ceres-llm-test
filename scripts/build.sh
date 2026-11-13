#!/usr/bin/env bash
# Build Ceres có bật đo độ phủ. Chạy trong container (run_docker.sh) hoặc trực tiếp trên Linux/WSL.
# Kết quả: thư mục build-cov/ với thư viện ceres, các test có sẵn,
#          và data/compile_commands.json cho bước phân tích AST.
set -euo pipefail

# REPO = gốc repo này, SRC = source Ceres (submodule ceres-solver/).
# Trong Docker, run_docker.sh đặt sẵn REPO_DIR=/work/repo, SRC_DIR=/work/ceres-solver.
REPO=${REPO_DIR:-$(cd "$(dirname "$0")/.." && pwd)}
SRC=${SRC_DIR:-$REPO/ceres-solver}
# Build để trên ổ Linux (nhanh). Trong Docker: /work/build-cov (volume). Ngoài Docker: ~/ceres-build-cov
if [ -d /work/build-cov ]; then DEFAULT_BUILD=/work/build-cov; else DEFAULT_BUILD=$HOME/ceres-build-cov; fi
BUILD=${BUILD_DIR:-$DEFAULT_BUILD}
JOBS=${JOBS:-$(nproc)}

cmake -S "$SRC" -B "$BUILD" -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ \
  -DCMAKE_C_FLAGS="--coverage -fprofile-update=atomic -O0" \
  -DCMAKE_CXX_FLAGS="--coverage -fprofile-update=atomic -O0" \
  -DCMAKE_EXE_LINKER_FLAGS="--coverage" \
  -DCMAKE_SHARED_LINKER_FLAGS="--coverage" \
  $(command -v ccache >/dev/null && echo -DCMAKE_CXX_COMPILER_LAUNCHER=ccache) \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DBUILD_TESTING=ON \
  -DBUILD_EXAMPLES=OFF \
  -DBUILD_BENCHMARKS=OFF \
  -DBUILD_DOCUMENTATION=OFF \
  -DMINIGLOG=OFF \
  -DGFLAGS=ON \
  -DUSE_CUDA=OFF \
  -DSUITESPARSE=OFF \
  -DLAPACK=OFF \
  -DEIGENSPARSE=ON \
  -DEIGENMETIS=OFF \
  -DSCHUR_SPECIALIZATIONS=OFF
# Tên option ở trên là của Ceres 2.2.0 (bản mới hơn đổi thành WITH_...).
# CMake KHÔNG báo lỗi khi gõ sai tên option, chỉ cảnh báo
# "Manually-specified variables were not used" -> kiểm tra dòng đó trong log build.

cmake --build "$BUILD" -j "$JOBS"

# Copy compile_commands.json ra repo để bước phân tích AST dùng
# (copy chứ không symlink, vì build nằm trong Docker volume, Windows không thấy)
mkdir -p "$REPO/data"
cp "$BUILD/compile_commands.json" "$REPO/data/compile_commands.json"
echo "BUILD OK -> $BUILD"
