// u1196 – ceres::internal::PartitionedMatrixView::UpdateBlockDiagonalFtFSingleThreaded
// Trích từ internal/ceres/partitioned_matrix_view_impl.h, dòng 530–580 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
void PartitionedMatrixView<kRowBlockSize, kEBlockSize, kFBlockSize>::
    UpdateBlockDiagonalFtFSingleThreaded(
        BlockSparseMatrix* block_diagonal) const {
  auto bs = matrix_.block_structure();
  auto block_diagonal_structure = block_diagonal->block_structure();

  block_diagonal->SetZero();
  const double* values = matrix_.values();
  for (int r = 0; r < num_row_blocks_e_; ++r) {
    const int row_block_size = bs->rows[r].block.size;
    const std::vector<Cell>& cells = bs->rows[r].cells;
    for (int c = 1; c < cells.size(); ++c) {
      const int col_block_id = cells[c].block_id;
      const int col_block_size = bs->cols[col_block_id].size;
      const int diagonal_block_id = col_block_id - num_col_blocks_e_;
      const int cell_position =
          block_diagonal_structure->rows[diagonal_block_id].cells[0].position;

      // clang-format off
      MatrixTransposeMatrixMultiply
          <kRowBlockSize, kFBlockSize, kRowBlockSize, kFBlockSize, 1>(
              values + cells[c].position, row_block_size, col_block_size,
              values + cells[c].position, row_block_size, col_block_size,
              block_diagonal->mutable_values() + cell_position,
              0, 0, col_block_size, col_block_size);
      // clang-format on
    }
  }

  for (int r = num_row_blocks_e_; r < bs->rows.size(); ++r) {
    const int row_block_size = bs->rows[r].block.size;
    const std::vector<Cell>& cells = bs->rows[r].cells;
    for (const auto& cell : cells) {
      const int col_block_id = cell.block_id;
      const int col_block_size = bs->cols[col_block_id].size;
      const int diagonal_block_id = col_block_id - num_col_blocks_e_;
      const int cell_position =
          block_diagonal_structure->rows[diagonal_block_id].cells[0].position;

      // clang-format off
      MatrixTransposeMatrixMultiply
          <Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic, 1>(
              values + cell.position, row_block_size, col_block_size,
              values + cell.position, row_block_size, col_block_size,
              block_diagonal->mutable_values() + cell_position,
              0, 0, col_block_size, col_block_size);
      // clang-format on
    }
  }
}
