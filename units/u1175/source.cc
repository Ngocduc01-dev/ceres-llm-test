// u1175 – ceres::internal::PartitionedMatrixView::UpdateBlockDiagonalEtEMultiThreaded
// Trích từ internal/ceres/partitioned_matrix_view_impl.h, dòng 474–512 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
void PartitionedMatrixView<kRowBlockSize, kEBlockSize, kFBlockSize>::
    UpdateBlockDiagonalEtEMultiThreaded(
        BlockSparseMatrix* block_diagonal) const {
  auto transpose_block_structure = matrix_.transpose_block_structure();
  CHECK(transpose_block_structure != nullptr);
  auto block_diagonal_structure = block_diagonal->block_structure();

  const double* values = matrix_.values();
  double* values_diagonal = block_diagonal->mutable_values();
  ParallelFor(
      options_.context,
      0,
      num_col_blocks_e_,
      options_.num_threads,
      [values,
       transpose_block_structure,
       values_diagonal,
       block_diagonal_structure](int col_block_id) {
        int cell_position =
            block_diagonal_structure->rows[col_block_id].cells[0].position;
        double* cell_values = values_diagonal + cell_position;
        int col_block_size =
            transpose_block_structure->rows[col_block_id].block.size;
        auto& cells = transpose_block_structure->rows[col_block_id].cells;
        MatrixRef(cell_values, col_block_size, col_block_size).setZero();

        for (auto& c : cells) {
          int row_block_size = transpose_block_structure->cols[c.block_id].size;
          // clang-format off
          MatrixTransposeMatrixMultiply<kRowBlockSize, kEBlockSize, kRowBlockSize, kEBlockSize, 1>(
            values + c.position, row_block_size, col_block_size,
            values + c.position, row_block_size, col_block_size,
            cell_values, 0, 0, col_block_size, col_block_size);
          // clang-format on
        }
      },
      e_cols_partition_);
}
