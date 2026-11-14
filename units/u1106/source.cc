// u1106 – ceres::internal::DynamicCompressedRowSparseMatrix::ClearRows
// Trích từ internal/ceres/dynamic_compressed_row_sparse_matrix.cc, dòng 55–63 (chỉ để xem, không compile)

void DynamicCompressedRowSparseMatrix::ClearRows(int row_start, int num_rows) {
  for (int r = 0; r < num_rows; ++r) {
    const int i = row_start + r;
    CHECK_GE(i, 0);
    CHECK_LT(i, this->num_rows());
    dynamic_cols_[i].resize(0);
    dynamic_values_[i].resize(0);
  }
}
