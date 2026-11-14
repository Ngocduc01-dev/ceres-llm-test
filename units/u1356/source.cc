// u1356 – ceres::internal::PartitionedMatrixView::UpdateBlockDiagonalEtE
// Trích từ internal/ceres/partitioned_matrix_view_impl.h, dòng 514–523 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
void PartitionedMatrixView<kRowBlockSize, kEBlockSize, kFBlockSize>::
    UpdateBlockDiagonalEtE(BlockSparseMatrix* block_diagonal) const {
  if (options_.num_threads == 1) {
    UpdateBlockDiagonalEtESingleThreaded(block_diagonal);
  } else {
    CHECK(options_.context != nullptr);
    UpdateBlockDiagonalEtEMultiThreaded(block_diagonal);
  }
}
