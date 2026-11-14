#!/usr/bin/env bash
set -euo pipefail

REPO=${REPO_DIR:-$(cd "$(dirname "$0")/.." && pwd)}
cd "$REPO"

if [ ! -f "data/graph.db" ]; then
  echo "Thiếu data/graph.db – hãy chạy scripts/phase1.sh trước." >&2
  exit 1
fi

python3 scripts/list_units.py
echo "PHASE 2 OK -> data/units.json, reports/units/summary.txt, data/smoke_test_units.txt"
