// u0944 – ceres::internal::BlockSparseMatrix::ToTextFile
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 557–579 (chỉ để xem, không compile)

void BlockSparseMatrix::ToTextFile(FILE* file) const {
  CHECK(file != nullptr);
  for (int i = 0; i < block_structure_->rows.size(); ++i) {
    const int row_block_pos = block_structure_->rows[i].block.position;
    const int row_block_size = block_structure_->rows[i].block.size;
    const auto& cells = block_structure_->rows[i].cells;
    for (const auto& cell : cells) {
      const int col_block_id = cell.block_id;
      const int col_block_size = block_structure_->cols[col_block_id].size;
      const int col_block_pos = block_structure_->cols[col_block_id].position;
      int jac_pos = cell.position;
      for (int r = 0; r < row_block_size; ++r) {
        for (int c = 0; c < col_block_size; ++c) {
          fprintf(file,
                  "% 10d % 10d %17f\n",
                  row_block_pos + r,
                  col_block_pos + c,
                  values_[jac_pos++]);
        }
      }
    }
  }
}
