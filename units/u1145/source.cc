// u1145 – ceres::internal::BlockSparseMatrix::SetZero
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 229–231 (chỉ để xem, không compile)

void BlockSparseMatrix::SetZero(ContextImpl* context, int num_threads) {
  ParallelSetZero(context, num_threads, values_, num_nonzeros_);
}
