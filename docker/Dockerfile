# Môi trường dùng chung cho cả nhóm: build Ceres, đo độ phủ, phân tích AST.
# Ubuntu 24.04 có sẵn GCC 14, CMake 3.28, Eigen 3.4, Clang 18 trong kho apt
# -> không phải tự build compiler hay thư viện nào.
FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
        # Compiler: GCC 14 (hỗ trợ đo nhánh và cả -fcondition-coverage nếu sau này cần C3)
        gcc-14 g++-14 make ninja-build cmake ccache git ca-certificates \
        # Thư viện Ceres 2.2.0 cần: Eigen (bắt buộc), glog + gflags (log, CHECK).
        # googletest đã có sẵn trong ceres-solver/internal/ceres/ (gmock_gtest_all.cc)
        libeigen3-dev libgoogle-glog-dev libgflags-dev \
        # Đo độ phủ
        lcov gcovr \
        # Phân tích tĩnh: Clang 18 + binding Python của libclang
        clang-18 libclang-18-dev python3-clang-18 \
        python3 python3-pip python3-venv \
    && rm -rf /var/lib/apt/lists/*

# Dùng GCC 14 làm mặc định (gcov phải cùng version với gcc, nên đổi luôn gcov)
RUN update-alternatives --install /usr/bin/gcc  gcc  /usr/bin/gcc-14  100 \
 && update-alternatives --install /usr/bin/g++  g++  /usr/bin/g++-14  100 \
 && update-alternatives --install /usr/bin/gcov gcov /usr/bin/gcov-14 100

# libclang Python binding cần biết file .so nằm ở đâu
ENV LIBCLANG_PATH=/usr/lib/llvm-18/lib/libclang.so
ENV CCACHE_DIR=/work/.ccache

WORKDIR /work/ceres-solver
