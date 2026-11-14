// u1425 – ceres::internal::PartitionedMatrixView::CreateBlockDiagonalFtF
// Trích từ internal/ceres/partitioned_matrix_view_impl.h, dòng 430–439 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
std::unique_ptr<BlockSparseMatrix>
PartitionedMatrixView<kRowBlockSize, kEBlockSize, kFBlockSize>::
    CreateBlockDiagonalFtF() const {
  std::unique_ptr<BlockSparseMatrix> block_diagonal =
      CreateBlockDiagonalMatrixLayout(num_col_blocks_e_,
                                      num_col_blocks_e_ + num_col_blocks_f_);
  UpdateBlockDiagonalFtF(block_diagonal.get());
  return block_diagonal;
}
