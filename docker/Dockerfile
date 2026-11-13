FROM ubuntu:24.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y \
    build-essential gcc-13 g++-13 cmake git dos2unix \
    libeigen3-dev libgoogle-glog-dev libgflags-dev libabsl-dev libgtest-dev \
    gcovr lcov python3 python3-pip python3-venv \
    libclang-dev clang \
    && rm -rf /var/lib/apt/lists/*
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 100 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-13 100 \
    && update-alternatives --install /usr/bin/gcov gcov /usr/bin/gcov-13 100
RUN pip3 install --break-system-packages libclang
WORKDIR /workspace
