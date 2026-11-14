// u1071 – ceres::internal::BlockRandomAccessDiagonalMatrix::SetZero
// Trích từ internal/ceres/block_random_access_diagonal_matrix.cc, dòng 85–88 (chỉ để xem, không compile)

void BlockRandomAccessDiagonalMatrix::SetZero() {
  ParallelSetZero(
      context_, num_threads_, m_->mutable_values(), m_->num_nonzeros());
}
