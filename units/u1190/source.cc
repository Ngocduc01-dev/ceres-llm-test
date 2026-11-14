// u1190 – ceres::internal::BlockSparseMatrix::SquaredColumnNorm
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 369–400 (chỉ để xem, không compile)

void BlockSparseMatrix::SquaredColumnNorm(double* x,
                                          ContextImpl* context,
                                          int num_threads) const {
  if (transpose_block_structure_ == nullptr || num_threads == 1) {
    SquaredColumnNorm(x);
    return;
  }

  CHECK(x != nullptr);
  ParallelSetZero(context, num_threads, x, num_cols_);

  auto transpose_bs = transpose_block_structure_.get();
  const auto values = values_;
  const int num_col_blocks = transpose_bs->rows.size();
  ParallelFor(
      context,
      0,
      num_col_blocks,
      num_threads,
      [values, transpose_bs, x](int row_block_id) {
        const auto& row = transpose_bs->rows[row_block_id];

        for (auto& cell : row.cells) {
          const auto& col = transpose_bs->cols[cell.block_id];
          const MatrixRef m(values + cell.position, col.size, row.block.size);
          VectorRef(x + row.block.position, row.block.size) +=
              m.colwise().squaredNorm();
        }
      },
      transpose_bs->rows.data(),
      [](const CompressedRow& row) { return row.cumulative_nnz; });
}
