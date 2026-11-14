// u1191 – ceres::internal::BlockSparseMatrix::ScaleColumns
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 420–449 (chỉ để xem, không compile)

void BlockSparseMatrix::ScaleColumns(const double* scale,
                                     ContextImpl* context,
                                     int num_threads) {
  if (transpose_block_structure_ == nullptr || num_threads == 1) {
    ScaleColumns(scale);
    return;
  }

  CHECK(scale != nullptr);
  auto transpose_bs = transpose_block_structure_.get();
  auto values = values_;
  const int num_col_blocks = transpose_bs->rows.size();
  ParallelFor(
      context,
      0,
      num_col_blocks,
      num_threads,
      [values, transpose_bs, scale](int row_block_id) {
        const auto& row = transpose_bs->rows[row_block_id];

        for (auto& cell : row.cells) {
          const auto& col = transpose_bs->cols[cell.block_id];
          MatrixRef m(values + cell.position, col.size, row.block.size);
          m *= ConstVectorRef(scale + row.block.position, row.block.size)
                   .asDiagonal();
        }
      },
      transpose_bs->rows.data(),
      [](const CompressedRow& row) { return row.cumulative_nnz; });
}
