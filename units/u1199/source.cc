// u1199 – ceres::internal::BlockSparseMatrix::ToTripletSparseMatrix
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 515–542 (chỉ để xem, không compile)

void BlockSparseMatrix::ToTripletSparseMatrix(
    TripletSparseMatrix* matrix) const {
  CHECK(matrix != nullptr);

  matrix->Reserve(num_nonzeros_);
  matrix->Resize(num_rows_, num_cols_);
  matrix->SetZero();

  for (int i = 0; i < block_structure_->rows.size(); ++i) {
    int row_block_pos = block_structure_->rows[i].block.position;
    int row_block_size = block_structure_->rows[i].block.size;
    const auto& cells = block_structure_->rows[i].cells;
    for (const auto& cell : cells) {
      int col_block_id = cell.block_id;
      int col_block_size = block_structure_->cols[col_block_id].size;
      int col_block_pos = block_structure_->cols[col_block_id].position;
      int jac_pos = cell.position;
      for (int r = 0; r < row_block_size; ++r) {
        for (int c = 0; c < col_block_size; ++c, ++jac_pos) {
          matrix->mutable_rows()[jac_pos] = row_block_pos + r;
          matrix->mutable_cols()[jac_pos] = col_block_pos + c;
          matrix->mutable_values()[jac_pos] = values_[jac_pos];
        }
      }
    }
  }
  matrix->set_num_nonzeros(num_nonzeros_);
}
