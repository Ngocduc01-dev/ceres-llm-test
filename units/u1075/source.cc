// u1075 – ceres::internal::DenseSparseMatrix::LeftMultiplyAndAccumulate
// Trích từ internal/ceres/dense_sparse_matrix.cc, dòng 67–71 (chỉ để xem, không compile)

void DenseSparseMatrix::LeftMultiplyAndAccumulate(const double* x,
                                                  double* y) const {
  VectorRef(y, num_cols()).noalias() +=
      m_.transpose() * ConstVectorRef(x, num_rows());
}
