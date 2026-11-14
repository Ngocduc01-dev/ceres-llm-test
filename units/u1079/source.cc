// u1079 – ceres::internal::PartitionedMatrixView::RightMultiplyAndAccumulateE
// Trích từ internal/ceres/partitioned_matrix_view_impl.h, dòng 112–137 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
void PartitionedMatrixView<kRowBlockSize, kEBlockSize, kFBlockSize>::
    RightMultiplyAndAccumulateE(const double* x, double* y) const {
  // Iterate over the first num_row_blocks_e_ row blocks, and multiply
  // by the first cell in each row block.
  auto bs = matrix_.block_structure();
  const double* values = matrix_.values();
  ParallelFor(options_.context,
              0,
              num_row_blocks_e_,
              options_.num_threads,
              [values, bs, x, y](int row_block_id) {
                const Cell& cell = bs->rows[row_block_id].cells[0];
                const int row_block_pos = bs->rows[row_block_id].block.position;
                const int row_block_size = bs->rows[row_block_id].block.size;
                const int col_block_id = cell.block_id;
                const int col_block_pos = bs->cols[col_block_id].position;
                const int col_block_size = bs->cols[col_block_id].size;
                // clang-format off
                MatrixVectorMultiply<kRowBlockSize, kEBlockSize, 1>(
                    values + cell.position, row_block_size, col_block_size,
                    x + col_block_pos,
                    y + row_block_pos);
                // clang-format on
              });
}
