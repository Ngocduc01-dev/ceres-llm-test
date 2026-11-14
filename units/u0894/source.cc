// u0894 – ceres::internal::SparseMatrix::SquaredColumnNorm
// Trích từ internal/ceres/sparse_matrix.cc, dòng 37–43 (chỉ để xem, không compile)

void SparseMatrix::SquaredColumnNorm(double* x,
                                     ContextImpl* context,
                                     int num_threads) const {
  (void)context;
  (void)num_threads;
  SquaredColumnNorm(x);
}
