// u1088 – ceres::internal::PartitionedMatrixView::LeftMultiplyAndAccumulateESingleThreaded
// Trích từ internal/ceres/partitioned_matrix_view_impl.h, dòng 206–228 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
void PartitionedMatrixView<kRowBlockSize, kEBlockSize, kFBlockSize>::
    LeftMultiplyAndAccumulateESingleThreaded(const double* x, double* y) const {
  const CompressedRowBlockStructure* bs = matrix_.block_structure();

  // Iterate over the first num_row_blocks_e_ row blocks, and multiply
  // by the first cell in each row block.
  const double* values = matrix_.values();
  for (int r = 0; r < num_row_blocks_e_; ++r) {
    const Cell& cell = bs->rows[r].cells[0];
    const int row_block_pos = bs->rows[r].block.position;
    const int row_block_size = bs->rows[r].block.size;
    const int col_block_id = cell.block_id;
    const int col_block_pos = bs->cols[col_block_id].position;
    const int col_block_size = bs->cols[col_block_id].size;
    // clang-format off
    MatrixTransposeVectorMultiply<kRowBlockSize, kEBlockSize, 1>(
        values + cell.position, row_block_size, col_block_size,
        x + row_block_pos,
        y + col_block_pos);
    // clang-format on
  }
}
