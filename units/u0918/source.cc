// u0918 – ceres::internal::CompressedRowSparseMatrix::ScaleColumns
// Trích từ internal/ceres/compressed_row_sparse_matrix.cc, dòng 434–440 (chỉ để xem, không compile)

void CompressedRowSparseMatrix::ScaleColumns(const double* scale) {
  CHECK(scale != nullptr);

  for (int idx = 0; idx < rows_[num_rows_]; ++idx) {
    values_[idx] *= scale[cols_[idx]];
  }
}
