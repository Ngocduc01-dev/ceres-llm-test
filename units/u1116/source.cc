// u1116 – ceres::internal::PartitionedMatrixView::LeftMultiplyAndAccumulateFMultiThreaded
// Trích từ internal/ceres/partitioned_matrix_view_impl.h, dòng 324–375 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
void PartitionedMatrixView<kRowBlockSize, kEBlockSize, kFBlockSize>::
    LeftMultiplyAndAccumulateFMultiThreaded(const double* x, double* y) const {
  auto transpose_bs = matrix_.transpose_block_structure();
  CHECK(transpose_bs != nullptr);
  // Local copies of class members  in order to avoid capturing pointer to the
  // whole object in lambda function
  auto values = matrix_.values();
  const int num_row_blocks_e = num_row_blocks_e_;
  const int num_cols_e = num_cols_e_;
  ParallelFor(
      options_.context,
      num_col_blocks_e_,
      num_col_blocks_e_ + num_col_blocks_f_,
      options_.num_threads,
      [values, transpose_bs, num_row_blocks_e, num_cols_e, x, y](
          int row_block_id) {
        int row_block_pos = transpose_bs->rows[row_block_id].block.position;
        int row_block_size = transpose_bs->rows[row_block_id].block.size;
        auto& cells = transpose_bs->rows[row_block_id].cells;

        const int num_cells = cells.size();
        int cell_idx = 0;
        for (; cell_idx < num_cells; ++cell_idx) {
          auto& cell = cells[cell_idx];
          const int col_block_id = cell.block_id;
          const int col_block_size = transpose_bs->cols[col_block_id].size;
          const int col_block_pos = transpose_bs->cols[col_block_id].position;
          if (col_block_id >= num_row_blocks_e) break;

          MatrixTransposeVectorMultiply<kRowBlockSize, kFBlockSize, 1>(
              values + cell.position,
              col_block_size,
              row_block_size,
              x + col_block_pos,
              y + row_block_pos - num_cols_e);
        }
        for (; cell_idx < num_cells; ++cell_idx) {
          auto& cell = cells[cell_idx];
          const int col_block_id = cell.block_id;
          const int col_block_size = transpose_bs->cols[col_block_id].size;
          const int col_block_pos = transpose_bs->cols[col_block_id].position;
          MatrixTransposeVectorMultiply<Eigen::Dynamic, Eigen::Dynamic, 1>(
              values + cell.position,
              col_block_size,
              row_block_size,
              x + col_block_pos,
              y + row_block_pos - num_cols_e);
        }
      },
      f_cols_partition());
}
