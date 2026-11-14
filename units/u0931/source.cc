// u0931 – ceres::internal::BlockSparseMatrix::ScaleColumns
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 402–416 (chỉ để xem, không compile)

void BlockSparseMatrix::ScaleColumns(const double* scale) {
  CHECK(scale != nullptr);

  for (int i = 0; i < block_structure_->rows.size(); ++i) {
    int row_block_size = block_structure_->rows[i].block.size;
    auto& cells = block_structure_->rows[i].cells;
    for (const auto& cell : cells) {
      int col_block_id = cell.block_id;
      int col_block_size = block_structure_->cols[col_block_id].size;
      int col_block_pos = block_structure_->cols[col_block_id].position;
      MatrixRef m(values_ + cell.position, row_block_size, col_block_size);
      m *= ConstVectorRef(scale + col_block_pos, col_block_size).asDiagonal();
    }
  }
}
