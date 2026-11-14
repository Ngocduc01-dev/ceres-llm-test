// u1296 – ceres::internal::PartitionedMatrixView::LeftMultiplyAndAccumulateE
// Trích từ internal/ceres/partitioned_matrix_view_impl.h, dòng 193–204 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
void PartitionedMatrixView<kRowBlockSize, kEBlockSize, kFBlockSize>::
    LeftMultiplyAndAccumulateE(const double* x, double* y) const {
  if (!num_col_blocks_e_) return;
  if (!num_row_blocks_e_) return;
  if (options_.num_threads == 1) {
    LeftMultiplyAndAccumulateESingleThreaded(x, y);
  } else {
    CHECK(options_.context != nullptr);
    LeftMultiplyAndAccumulateEMultiThreaded(x, y);
  }
}
