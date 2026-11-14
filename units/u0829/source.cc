// u0829 – ceres::internal::BlockSparseMatrix::SetZero
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 225–227 (chỉ để xem, không compile)

void BlockSparseMatrix::SetZero() {
  std::fill(values_, values_ + num_nonzeros_, 0.0);
}
