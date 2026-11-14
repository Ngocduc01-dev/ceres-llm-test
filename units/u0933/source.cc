// u0933 – ceres::internal::CompressedRowSparseMatrix::ToDenseMatrix
// Trích từ internal/ceres/compressed_row_sparse_matrix.cc, dòng 442–452 (chỉ để xem, không compile)

void CompressedRowSparseMatrix::ToDenseMatrix(Matrix* dense_matrix) const {
  CHECK(dense_matrix != nullptr);
  dense_matrix->resize(num_rows_, num_cols_);
  dense_matrix->setZero();

  for (int r = 0; r < num_rows_; ++r) {
    for (int idx = rows_[r]; idx < rows_[r + 1]; ++idx) {
      (*dense_matrix)(r, cols_[idx]) = values_[idx];
    }
  }
}
