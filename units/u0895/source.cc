// u0895 – ceres::internal::SparseMatrix::ScaleColumns
// Trích từ internal/ceres/sparse_matrix.cc, dòng 45–51 (chỉ để xem, không compile)

void SparseMatrix::ScaleColumns(const double* scale,
                                ContextImpl* context,
                                int num_threads) {
  (void)context;
  (void)num_threads;
  ScaleColumns(scale);
}
