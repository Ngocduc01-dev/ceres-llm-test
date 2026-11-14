// u1163 – ceres::internal::PartitionedMatrixView::UpdateBlockDiagonalEtESingleThreaded
// Trích từ internal/ceres/partitioned_matrix_view_impl.h, dòng 446–472 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
void PartitionedMatrixView<kRowBlockSize, kEBlockSize, kFBlockSize>::
    UpdateBlockDiagonalEtESingleThreaded(
        BlockSparseMatrix* block_diagonal) const {
  auto bs = matrix_.block_structure();
  auto block_diagonal_structure = block_diagonal->block_structure();

  block_diagonal->SetZero();
  const double* values = matrix_.values();
  for (int r = 0; r < num_row_blocks_e_; ++r) {
    const Cell& cell = bs->rows[r].cells[0];
    const int row_block_size = bs->rows[r].block.size;
    const int block_id = cell.block_id;
    const int col_block_size = bs->cols[block_id].size;
    const int cell_position =
        block_diagonal_structure->rows[block_id].cells[0].position;

    // clang-format off
    MatrixTransposeMatrixMultiply
        <kRowBlockSize, kEBlockSize, kRowBlockSize, kEBlockSize, 1>(
            values + cell.position, row_block_size, col_block_size,
            values + cell.position, row_block_size, col_block_size,
            block_diagonal->mutable_values() + cell_position,
            0, 0, col_block_size, col_block_size);
    // clang-format on
  }
}
