// u1204 – ceres::internal::BlockSparseMatrix::LeftMultiplyAndAccumulate
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 277–324 (chỉ để xem, không compile)

void BlockSparseMatrix::LeftMultiplyAndAccumulate(const double* x,
                                                  double* y,
                                                  ContextImpl* context,
                                                  int num_threads) const {
  // While utilizing transposed structure allows to perform parallel
  // left-multiplication by dense vector, it makes access patterns to matrix
  // elements scattered. Thus, multiplication using transposed structure
  // is only useful for parallel execution
  CHECK(x != nullptr);
  CHECK(y != nullptr);
  if (transpose_block_structure_ == nullptr || num_threads == 1) {
    LeftMultiplyAndAccumulate(x, y);
    return;
  }

  auto transpose_bs = transpose_block_structure_.get();
  const auto values = values_;
  const int num_col_blocks = transpose_bs->rows.size();
  if (!num_col_blocks) {
    return;
  }

  // Use non-zero count as iteration cost for guided parallel-for loop
  ParallelFor(
      context,
      0,
      num_col_blocks,
      num_threads,
      [values, transpose_bs, x, y](int row_block_id) {
        int row_block_pos = transpose_bs->rows[row_block_id].block.position;
        int row_block_size = transpose_bs->rows[row_block_id].block.size;
        auto& cells = transpose_bs->rows[row_block_id].cells;

        for (auto& cell : cells) {
          const int col_block_id = cell.block_id;
          const int col_block_size = transpose_bs->cols[col_block_id].size;
          const int col_block_pos = transpose_bs->cols[col_block_id].position;
          MatrixTransposeVectorMultiply<Eigen::Dynamic, Eigen::Dynamic, 1>(
              values + cell.position,
              col_block_size,
              row_block_size,
              x + col_block_pos,
              y + row_block_pos);
        }
      },
      transpose_bs->rows.data(),
      [](const CompressedRow& row) { return row.cumulative_nnz; });
}
