// u0915 – ceres::internal::TripletSparseMatrix::LeftMultiplyAndAccumulate
// Trích từ internal/ceres/triplet_sparse_matrix.cc, dòng 179–184 (chỉ để xem, không compile)

void TripletSparseMatrix::LeftMultiplyAndAccumulate(const double* x,
                                                    double* y) const {
  for (int i = 0; i < num_nonzeros_; ++i) {
    y[cols_[i]] += values_[i] * x[rows_[i]];
  }
}
