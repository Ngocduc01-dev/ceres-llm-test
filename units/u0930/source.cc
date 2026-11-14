// u0930 – ceres::internal::BlockSparseMatrix::SquaredColumnNorm
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 350–365 (chỉ để xem, không compile)

void BlockSparseMatrix::SquaredColumnNorm(double* x) const {
  CHECK(x != nullptr);
  VectorRef(x, num_cols_).setZero();
  for (int i = 0; i < block_structure_->rows.size(); ++i) {
    int row_block_size = block_structure_->rows[i].block.size;
    auto& cells = block_structure_->rows[i].cells;
    for (const auto& cell : cells) {
      int col_block_id = cell.block_id;
      int col_block_size = block_structure_->cols[col_block_id].size;
      int col_block_pos = block_structure_->cols[col_block_id].position;
      const MatrixRef m(
          values_ + cell.position, row_block_size, col_block_size);
      VectorRef(x + col_block_pos, col_block_size) += m.colwise().squaredNorm();
    }
  }
}
