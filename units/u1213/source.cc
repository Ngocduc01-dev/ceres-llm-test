// u1213 – ceres::internal::BlockRandomAccessSparseMatrix::BlockRandomAccessSparseMatrix
// Trích từ internal/ceres/block_random_access_sparse_matrix.cc, dòng 47–98 (chỉ để xem, không compile)

BlockRandomAccessSparseMatrix::BlockRandomAccessSparseMatrix(
    const std::vector<Block>& blocks,
    const std::set<std::pair<int, int>>& block_pairs,
    ContextImpl* context,
    int num_threads)
    : blocks_(blocks), context_(context), num_threads_(num_threads) {
  CHECK_LE(blocks.size(), std::numeric_limits<std::int32_t>::max());

  const int num_cols = NumScalarEntries(blocks);
  const int num_blocks = blocks.size();

  std::vector<int> num_cells_at_row(num_blocks);
  for (auto& p : block_pairs) {
    ++num_cells_at_row[p.first];
  }
  auto block_structure_ = new CompressedRowBlockStructure;
  block_structure_->cols = blocks;
  block_structure_->rows.resize(num_blocks);
  auto p = block_pairs.begin();
  int num_nonzeros = 0;
  // Pairs of block indices are sorted lexicographically, thus pairs
  // corresponding to a single row-block are stored in segments of index pairs
  // with constant row-block index and increasing column-block index.
  // CompressedRowBlockStructure is created by traversing block_pairs set.
  for (int row_block_id = 0; row_block_id < num_blocks; ++row_block_id) {
    auto& row = block_structure_->rows[row_block_id];
    row.block = blocks[row_block_id];
    row.cells.reserve(num_cells_at_row[row_block_id]);
    const int row_block_size = blocks[row_block_id].size;
    // Process all index pairs corresponding to the current row block. Because
    // index pairs are sorted lexicographically, cells are being appended to the
    // current row-block till the first change in row-block index
    for (; p != block_pairs.end() && row_block_id == p->first; ++p) {
      const int col_block_id = p->second;
      row.cells.emplace_back(col_block_id, num_nonzeros);
      num_nonzeros += row_block_size * blocks[col_block_id].size;
    }
  }
  bsm_ = std::make_unique<BlockSparseMatrix>(block_structure_);
  VLOG(1) << "Matrix Size [" << num_cols << "," << num_cols << "] "
          << num_nonzeros;
  double* values = bsm_->mutable_values();
  for (int row_block_id = 0; row_block_id < num_blocks; ++row_block_id) {
    const auto& cells = block_structure_->rows[row_block_id].cells;
    for (auto& c : cells) {
      const int col_block_id = c.block_id;
      double* const data = values + c.position;
      layout_[IntPairToInt64(row_block_id, col_block_id)] =
          std::make_unique<CellInfo>(data);
    }
  }
}
