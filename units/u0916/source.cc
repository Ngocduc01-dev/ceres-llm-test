// u0916 – ceres::internal::TripletSparseMatrix::ToDenseMatrix
// Trích từ internal/ceres/triplet_sparse_matrix.cc, dòng 206–213 (chỉ để xem, không compile)

void TripletSparseMatrix::ToDenseMatrix(Matrix* dense_matrix) const {
  dense_matrix->resize(num_rows_, num_cols_);
  dense_matrix->setZero();
  Matrix& m = *dense_matrix;
  for (int i = 0; i < num_nonzeros_; ++i) {
    m(rows_[i], cols_[i]) += values_[i];
  }
}
