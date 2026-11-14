// u1115 – ceres::internal::PartitionedMatrixView::LeftMultiplyAndAccumulateFSingleThreaded
// Trích từ internal/ceres/partitioned_matrix_view_impl.h, dòng 278–322 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
void PartitionedMatrixView<kRowBlockSize, kEBlockSize, kFBlockSize>::
    LeftMultiplyAndAccumulateFSingleThreaded(const double* x, double* y) const {
  const CompressedRowBlockStructure* bs = matrix_.block_structure();

  // Iterate over row blocks, and if the row block is in E, then
  // multiply by all the cells except the first one which is of type
  // E. If the row block is not in E (i.e its in the bottom
  // num_row_blocks - num_row_blocks_e row blocks), then all the cells
  // are of type F and multiply by them all.
  const double* values = matrix_.values();
  for (int r = 0; r < num_row_blocks_e_; ++r) {
    const int row_block_pos = bs->rows[r].block.position;
    const int row_block_size = bs->rows[r].block.size;
    const std::vector<Cell>& cells = bs->rows[r].cells;
    for (int c = 1; c < cells.size(); ++c) {
      const int col_block_id = cells[c].block_id;
      const int col_block_pos = bs->cols[col_block_id].position;
      const int col_block_size = bs->cols[col_block_id].size;
      // clang-format off
      MatrixTransposeVectorMultiply<kRowBlockSize, kFBlockSize, 1>(
        values + cells[c].position, row_block_size, col_block_size,
        x + row_block_pos,
        y + col_block_pos - num_cols_e_);
      // clang-format on
    }
  }

  for (int r = num_row_blocks_e_; r < bs->rows.size(); ++r) {
    const int row_block_pos = bs->rows[r].block.position;
    const int row_block_size = bs->rows[r].block.size;
    const std::vector<Cell>& cells = bs->rows[r].cells;
    for (const auto& cell : cells) {
      const int col_block_id = cell.block_id;
      const int col_block_pos = bs->cols[col_block_id].position;
      const int col_block_size = bs->cols[col_block_id].size;
      // clang-format off
      MatrixTransposeVectorMultiply<Eigen::Dynamic, Eigen::Dynamic, 1>(
        values + cell.position, row_block_size, col_block_size,
        x + row_block_pos,
        y + col_block_pos - num_cols_e_);
      // clang-format on
    }
  }
}
