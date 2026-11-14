// u1365 – ceres::internal::CompressedRowSparseMatrix::LeftMultiplyAndAccumulate
// Trích từ internal/ceres/compressed_row_sparse_matrix.cc, dòng 360–376 (chỉ để xem, không compile)

void CompressedRowSparseMatrix::LeftMultiplyAndAccumulate(const double* x,
                                                          double* y) const {
  CHECK(x != nullptr);
  CHECK(y != nullptr);

  if (storage_type_ == StorageType::UNSYMMETRIC) {
    for (int r = 0; r < num_rows_; ++r) {
      for (int idx = rows_[r]; idx < rows_[r + 1]; ++idx) {
        y[cols_[idx]] += values_[idx] * x[r];
      }
    }
  } else {
    // Since the matrix is symmetric, LeftMultiplyAndAccumulate =
    // RightMultiplyAndAccumulate.
    RightMultiplyAndAccumulate(x, y);
  }
}
