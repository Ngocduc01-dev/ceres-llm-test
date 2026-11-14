// u1357 – ceres::internal::PartitionedMatrixView::UpdateBlockDiagonalFtF
// Trích từ internal/ceres/partitioned_matrix_view_impl.h, dòng 649–658 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
void PartitionedMatrixView<kRowBlockSize, kEBlockSize, kFBlockSize>::
    UpdateBlockDiagonalFtF(BlockSparseMatrix* block_diagonal) const {
  if (options_.num_threads == 1) {
    UpdateBlockDiagonalFtFSingleThreaded(block_diagonal);
  } else {
    CHECK(options_.context != nullptr);
    UpdateBlockDiagonalFtFMultiThreaded(block_diagonal);
  }
}
