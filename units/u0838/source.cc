// u0838 – ceres::internal::CompressedRowSparseMatrix::SetZero
// Trích từ internal/ceres/compressed_row_sparse_matrix.cc, dòng 277–279 (chỉ để xem, không compile)

void CompressedRowSparseMatrix::SetZero() {
  std::fill(values_.begin(), values_.end(), 0);
}
