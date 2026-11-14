// u1197 – ceres::internal::PartitionedMatrixView::UpdateBlockDiagonalFtFMultiThreaded
// Trích từ internal/ceres/partitioned_matrix_view_impl.h, dòng 582–647 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
void PartitionedMatrixView<kRowBlockSize, kEBlockSize, kFBlockSize>::
    UpdateBlockDiagonalFtFMultiThreaded(
        BlockSparseMatrix* block_diagonal) const {
  auto transpose_block_structure = matrix_.transpose_block_structure();
  CHECK(transpose_block_structure != nullptr);
  auto block_diagonal_structure = block_diagonal->block_structure();

  const double* values = matrix_.values();
  double* values_diagonal = block_diagonal->mutable_values();

  const int num_col_blocks_e = num_col_blocks_e_;
  const int num_row_blocks_e = num_row_blocks_e_;
  ParallelFor(
      options_.context,
      num_col_blocks_e_,
      num_col_blocks_e + num_col_blocks_f_,
      options_.num_threads,
      [transpose_block_structure,
       block_diagonal_structure,
       num_col_blocks_e,
       num_row_blocks_e,
       values,
       values_diagonal](int col_block_id) {
        const int col_block_size =
            transpose_block_structure->rows[col_block_id].block.size;
        const int diagonal_block_id = col_block_id - num_col_blocks_e;
        const int cell_position =
            block_diagonal_structure->rows[diagonal_block_id].cells[0].position;
        double* cell_values = values_diagonal + cell_position;

        MatrixRef(cell_values, col_block_size, col_block_size).setZero();

        auto& cells = transpose_block_structure->rows[col_block_id].cells;
        const int num_cells = cells.size();
        int i = 0;
        for (; i < num_cells; ++i) {
          auto& cell = cells[i];
          const int row_block_id = cell.block_id;
          if (row_block_id >= num_row_blocks_e) break;
          const int row_block_size =
              transpose_block_structure->cols[row_block_id].size;
          // clang-format off
          MatrixTransposeMatrixMultiply
              <kRowBlockSize, kFBlockSize, kRowBlockSize, kFBlockSize, 1>(
                  values + cell.position, row_block_size, col_block_size,
                  values + cell.position, row_block_size, col_block_size,
                  cell_values, 0, 0, col_block_size, col_block_size);
          // clang-format on
        }
        for (; i < num_cells; ++i) {
          auto& cell = cells[i];
          const int row_block_id = cell.block_id;
          const int row_block_size =
              transpose_block_structure->cols[row_block_id].size;
          // clang-format off
          MatrixTransposeMatrixMultiply
              <Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic, 1>(
                  values + cell.position, row_block_size, col_block_size,
                  values + cell.position, row_block_size, col_block_size,
                  cell_values, 0, 0, col_block_size, col_block_size);
          // clang-format on
        }
      },
      f_cols_partition_);
}
