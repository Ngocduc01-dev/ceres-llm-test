// u0773 – ceres::internal::CompressedColumnScalarMatrixToBlockMatrix
// Trích từ internal/ceres/compressed_col_sparse_matrix_utils.cc, dòng 41–89 (chỉ để xem, không compile)

void CompressedColumnScalarMatrixToBlockMatrix(
    const int* scalar_rows,
    const int* scalar_cols,
    const std::vector<Block>& row_blocks,
    const std::vector<Block>& col_blocks,
    std::vector<int>* block_rows,
    std::vector<int>* block_cols) {
  CHECK(block_rows != nullptr);
  CHECK(block_cols != nullptr);
  block_rows->clear();
  block_cols->clear();
  const int num_col_blocks = col_blocks.size();

  // This loop extracts the block sparsity of the scalar sparse matrix
  // It does so by iterating over the columns, but only considering
  // the columns corresponding to the first element of each column
  // block. Within each column, the inner loop iterates over the rows,
  // and detects the presence of a row block by checking for the
  // presence of a non-zero entry corresponding to its first element.
  block_cols->push_back(0);
  int c = 0;
  for (int col_block = 0; col_block < num_col_blocks; ++col_block) {
    int column_size = 0;
    for (int idx = scalar_cols[c]; idx < scalar_cols[c + 1]; ++idx) {
      auto it = std::lower_bound(row_blocks.begin(),
                                 row_blocks.end(),
                                 scalar_rows[idx],
                                 [](const Block& block, double value) {
                                   return block.position < value;
                                 });
      // Since we are using lower_bound, it will return the row id where the row
      // block starts. For everything but the first row of the block, where
      // these values will be the same, we can skip, as we only need the first
      // row to detect the presence of the block.
      //
      // For rows all but the first row in the last row block, lower_bound will
      // return row_blocks_.end(), but those can be skipped like the rows in
      // other row blocks too.
      if (it == row_blocks.end() || it->position != scalar_rows[idx]) {
        continue;
      }

      block_rows->push_back(it - row_blocks.begin());
      ++column_size;
    }
    block_cols->push_back(block_cols->back() + column_size);
    c += col_blocks[col_block].size;
  }
}
