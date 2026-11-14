#!/usr/bin/env bash
set -euo pipefail
cd "${REPO_DIR:-$(cd "$(dirname "$0")/.." && pwd)}"
mkdir -p data/context reports/context logs/raw
python3 scripts/build_context.py | tee logs/raw/phase3.log
