// u1146 – ceres::internal::BlockSparseMatrix::RightMultiplyAndAccumulate
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 233–236 (chỉ để xem, không compile)

void BlockSparseMatrix::RightMultiplyAndAccumulate(const double* x,
                                                   double* y) const {
  RightMultiplyAndAccumulate(x, y, nullptr, 1);
}
