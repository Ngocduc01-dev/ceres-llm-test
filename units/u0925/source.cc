// u0925 – ceres::internal::TripletSparseMatrix::SquaredColumnNorm
// Trích từ internal/ceres/triplet_sparse_matrix.cc, dòng 186–192 (chỉ để xem, không compile)

void TripletSparseMatrix::SquaredColumnNorm(double* x) const {
  CHECK(x != nullptr);
  VectorRef(x, num_cols_).setZero();
  for (int i = 0; i < num_nonzeros_; ++i) {
    x[cols_[i]] += values_[i] * values_[i];
  }
}
