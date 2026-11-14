// u1284 – ceres::internal::BlockRandomAccessSparseMatrix::SetZero
// Trích từ internal/ceres/block_random_access_sparse_matrix.cc, dòng 121–123 (chỉ để xem, không compile)

void BlockRandomAccessSparseMatrix::SetZero() {
  bsm_->SetZero(context_, num_threads_);
}
