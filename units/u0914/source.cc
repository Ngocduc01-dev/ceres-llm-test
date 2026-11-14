// u0914 – ceres::internal::TripletSparseMatrix::RightMultiplyAndAccumulate
// Trích từ internal/ceres/triplet_sparse_matrix.cc, dòng 172–177 (chỉ để xem, không compile)

void TripletSparseMatrix::RightMultiplyAndAccumulate(const double* x,
                                                     double* y) const {
  for (int i = 0; i < num_nonzeros_; ++i) {
    y[rows_[i]] += values_[i] * x[cols_[i]];
  }
}
