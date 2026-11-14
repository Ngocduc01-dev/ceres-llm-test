// u1424 – ceres::internal::PartitionedMatrixView::CreateBlockDiagonalEtE
// Trích từ internal/ceres/partitioned_matrix_view_impl.h, dòng 420–428 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
std::unique_ptr<BlockSparseMatrix>
PartitionedMatrixView<kRowBlockSize, kEBlockSize, kFBlockSize>::
    CreateBlockDiagonalEtE() const {
  std::unique_ptr<BlockSparseMatrix> block_diagonal =
      CreateBlockDiagonalMatrixLayout(0, num_col_blocks_e_);
  UpdateBlockDiagonalEtE(block_diagonal.get());
  return block_diagonal;
}
