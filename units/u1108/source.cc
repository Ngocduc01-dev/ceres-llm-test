// u1108 – ceres::internal::PartitionedMatrixView::LeftMultiplyAndAccumulateEMultiThreaded
// Trích từ internal/ceres/partitioned_matrix_view_impl.h, dòng 230–264 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
void PartitionedMatrixView<kRowBlockSize, kEBlockSize, kFBlockSize>::
    LeftMultiplyAndAccumulateEMultiThreaded(const double* x, double* y) const {
  auto transpose_bs = matrix_.transpose_block_structure();
  CHECK(transpose_bs != nullptr);

  // Local copies of class members in order to avoid capturing pointer to the
  // whole object in lambda function
  auto values = matrix_.values();
  const int num_row_blocks_e = num_row_blocks_e_;
  ParallelFor(
      options_.context,
      0,
      num_col_blocks_e_,
      options_.num_threads,
      [values, transpose_bs, num_row_blocks_e, x, y](int row_block_id) {
        int row_block_pos = transpose_bs->rows[row_block_id].block.position;
        int row_block_size = transpose_bs->rows[row_block_id].block.size;
        auto& cells = transpose_bs->rows[row_block_id].cells;

        for (auto& cell : cells) {
          const int col_block_id = cell.block_id;
          const int col_block_size = transpose_bs->cols[col_block_id].size;
          const int col_block_pos = transpose_bs->cols[col_block_id].position;
          if (col_block_id >= num_row_blocks_e) break;
          MatrixTransposeVectorMultiply<kRowBlockSize, kEBlockSize, 1>(
              values + cell.position,
              col_block_size,
              row_block_size,
              x + col_block_pos,
              y + row_block_pos);
        }
      },
      e_cols_partition());
}
