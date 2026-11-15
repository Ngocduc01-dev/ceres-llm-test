#!/usr/bin/env bash
# Chạy Phase 6 cho toàn bộ Unit có file *_test.cc trong Docker.
#
# Ví dụ:
#   scripts/run_all_unit_tests.sh
#   scripts/run_all_unit_tests.sh -j 8
#   scripts/run_all_unit_tests.sh --ids u0251 u0252 -j 4
#   scripts/run_all_unit_tests.sh --report-only
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO="$(cd "$SCRIPT_DIR/.." && pwd)"

exec "$SCRIPT_DIR/run_docker.sh" \
  python3 scripts/phase6.py "$@"
