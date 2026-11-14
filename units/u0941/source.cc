// u0941 – ceres::internal::BlockSparseMatrix::LeftMultiplyAndAccumulate
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 326–348 (chỉ để xem, không compile)

void BlockSparseMatrix::LeftMultiplyAndAccumulate(const double* x,
                                                  double* y) const {
  CHECK(x != nullptr);
  CHECK(y != nullptr);
  // Single-threaded left products are always computed using a non-transpose
  // block structure, because it has linear acess pattern to matrix elements
  for (int i = 0; i < block_structure_->rows.size(); ++i) {
    int row_block_pos = block_structure_->rows[i].block.position;
    int row_block_size = block_structure_->rows[i].block.size;
    const auto& cells = block_structure_->rows[i].cells;
    for (const auto& cell : cells) {
      int col_block_id = cell.block_id;
      int col_block_size = block_structure_->cols[col_block_id].size;
      int col_block_pos = block_structure_->cols[col_block_id].position;
      MatrixTransposeVectorMultiply<Eigen::Dynamic, Eigen::Dynamic, 1>(
          values_ + cell.position,
          row_block_size,
          col_block_size,
          x + row_block_pos,
          y + col_block_pos);
    }
  }
}
