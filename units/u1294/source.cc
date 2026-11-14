// u1294 – ceres::internal::PartitionedMatrixView::LeftMultiplyAndAccumulateF
// Trích từ internal/ceres/partitioned_matrix_view_impl.h, dòng 266–276 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
void PartitionedMatrixView<kRowBlockSize, kEBlockSize, kFBlockSize>::
    LeftMultiplyAndAccumulateF(const double* x, double* y) const {
  if (!num_col_blocks_f_) return;
  if (options_.num_threads == 1) {
    LeftMultiplyAndAccumulateFSingleThreaded(x, y);
  } else {
    CHECK(options_.context != nullptr);
    LeftMultiplyAndAccumulateFMultiThreaded(x, y);
  }
}
