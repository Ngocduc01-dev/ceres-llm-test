// u0722 – ceres::internal::DenseSparseMatrix::SquaredColumnNorm
// Trích từ internal/ceres/dense_sparse_matrix.cc, dòng 73–87 (chỉ để xem, không compile)

void DenseSparseMatrix::SquaredColumnNorm(double* x) const {
  // This implementation is 3x faster than the naive version
  // x = m_.colwise().square().sum(), likely because m_
  // is a row major matrix.

  const int num_rows = m_.rows();
  const int num_cols = m_.cols();
  std::fill_n(x, num_cols, 0.0);
  const double* m = m_.data();
  for (int i = 0; i < num_rows; ++i) {
    for (int j = 0; j < num_cols; ++j, ++m) {
      x[j] += (*m) * (*m);
    }
  }
}
