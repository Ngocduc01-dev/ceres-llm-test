#!/bin/bash
set -e
cd /home/ngocduc/ceres-llm-test/ceres-solver
rm -rf build
mkdir build && cd build
cmake .. \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_CXX_FLAGS="--coverage -O0" \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DBUILD_EXAMPLES=OFF \
  -DBUILD_BENCHMARKS=OFF \
  -DSUITESPARSE=OFF \
  -DLAPACK=OFF \
  -DMINIGLOG=OFF
make -j1
