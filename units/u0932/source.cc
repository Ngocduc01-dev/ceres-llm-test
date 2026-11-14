// u0932 – ceres::internal::BlockSparseMatrix::ToDenseMatrix
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 493–513 (chỉ để xem, không compile)

void BlockSparseMatrix::ToDenseMatrix(Matrix* dense_matrix) const {
  CHECK(dense_matrix != nullptr);

  dense_matrix->resize(num_rows_, num_cols_);
  dense_matrix->setZero();
  Matrix& m = *dense_matrix;

  for (int i = 0; i < block_structure_->rows.size(); ++i) {
    int row_block_pos = block_structure_->rows[i].block.position;
    int row_block_size = block_structure_->rows[i].block.size;
    auto& cells = block_structure_->rows[i].cells;
    for (const auto& cell : cells) {
      int col_block_id = cell.block_id;
      int col_block_size = block_structure_->cols[col_block_id].size;
      int col_block_pos = block_structure_->cols[col_block_id].position;
      int jac_pos = cell.position;
      m.block(row_block_pos, col_block_pos, row_block_size, col_block_size) +=
          MatrixRef(values_ + jac_pos, row_block_size, col_block_size);
    }
  }
}
