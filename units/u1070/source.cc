// u1070 – ceres::internal::BlockRandomAccessDenseMatrix::SetZero
// Trích từ internal/ceres/block_random_access_dense_matrix.cc, dòng 71–73 (chỉ để xem, không compile)

void BlockRandomAccessDenseMatrix::SetZero() {
  ParallelSetZero(context_, num_threads_, values_.get(), num_rows_ * num_rows_);
}
