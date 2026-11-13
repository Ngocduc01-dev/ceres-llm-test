#!/bin/bash
set -e
cd /home/ngocduc/ceres-llm-test/ceres-solver/build
ctest --output-on-failure -j$(nproc)
gcovr -r /home/ngocduc/ceres-llm-test/ceres-solver \
  --filter "/home/ngocduc/ceres-llm-test/ceres-solver/internal/ceres/" \
  --filter "/home/ngocduc/ceres-llm-test/ceres-solver/include/ceres/" \
  --exclude "/home/ngocduc/ceres-llm-test/ceres-solver/internal/ceres/generated/" \
  --exclude ".*_test\.cc$" \
  --exclude-throw-branches \
  --exclude-unreachable-branches \
  --print-summary \
  --json-summary /home/ngocduc/ceres-llm-test/report/baseline_coverage.json
