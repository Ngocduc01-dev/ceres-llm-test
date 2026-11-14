// u1074 – ceres::internal::DenseSparseMatrix::RightMultiplyAndAccumulate
// Trích từ internal/ceres/dense_sparse_matrix.cc, dòng 62–65 (chỉ để xem, không compile)

void DenseSparseMatrix::RightMultiplyAndAccumulate(const double* x,
                                                   double* y) const {
  VectorRef(y, num_rows()).noalias() += m_ * ConstVectorRef(x, num_cols());
}
