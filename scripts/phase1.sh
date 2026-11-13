#!/usr/bin/env bash
# Phase 1 – chạy toàn bộ: dựng code graph -> xuất HTML graph -> xuất HTML AST.
# Cần chạy build.sh trước (để có data/compile_commands.json).
#   scripts/run_docker.sh env JOBS=4 bash scripts/phase1.sh
set -euo pipefail
cd "${REPO_DIR:-$(cd "$(dirname "$0")/.." && pwd)}"
[ -f data/compile_commands.json ] || { echo "Thiếu data/compile_commands.json – chạy scripts/build.sh trước"; exit 1; }

echo "== 1/3 Dựng code graph (data/graph.db)"
python3 scripts/build_graph.py
echo "== 2/3 Xuất reports/graph/graph.html"
python3 scripts/viz_graph.py
echo "== 3/3 Xuất reports/ast/ast.html"
python3 scripts/ast_export.py
echo "PHASE 1 OK"
