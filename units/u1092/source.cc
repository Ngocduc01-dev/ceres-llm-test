// u1092 – ceres::internal::PartitionedMatrixView::RightMultiplyAndAccumulateF
// Trích từ internal/ceres/partitioned_matrix_view_impl.h, dòng 139–191 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
void PartitionedMatrixView<kRowBlockSize, kEBlockSize, kFBlockSize>::
    RightMultiplyAndAccumulateF(const double* x, double* y) const {
  // Iterate over row blocks, and if the row block is in E, then
  // multiply by all the cells except the first one which is of type
  // E. If the row block is not in E (i.e its in the bottom
  // num_row_blocks - num_row_blocks_e row blocks), then all the cells
  // are of type F and multiply by them all.
  const CompressedRowBlockStructure* bs = matrix_.block_structure();
  const int num_row_blocks = bs->rows.size();
  const int num_cols_e = num_cols_e_;
  const double* values = matrix_.values();
  ParallelFor(options_.context,
              0,
              num_row_blocks_e_,
              options_.num_threads,
              [values, bs, num_cols_e, x, y](int row_block_id) {
                const int row_block_pos = bs->rows[row_block_id].block.position;
                const int row_block_size = bs->rows[row_block_id].block.size;
                const auto& cells = bs->rows[row_block_id].cells;
                for (int c = 1; c < cells.size(); ++c) {
                  const int col_block_id = cells[c].block_id;
                  const int col_block_pos = bs->cols[col_block_id].position;
                  const int col_block_size = bs->cols[col_block_id].size;
                  // clang-format off
                  MatrixVectorMultiply<kRowBlockSize, kFBlockSize, 1>(
                      values + cells[c].position, row_block_size, col_block_size,
                      x + col_block_pos - num_cols_e,
                      y + row_block_pos);
                  // clang-format on
                }
              });
  ParallelFor(options_.context,
              num_row_blocks_e_,
              num_row_blocks,
              options_.num_threads,
              [values, bs, num_cols_e, x, y](int row_block_id) {
                const int row_block_pos = bs->rows[row_block_id].block.position;
                const int row_block_size = bs->rows[row_block_id].block.size;
                const auto& cells = bs->rows[row_block_id].cells;
                for (const auto& cell : cells) {
                  const int col_block_id = cell.block_id;
                  const int col_block_pos = bs->cols[col_block_id].position;
                  const int col_block_size = bs->cols[col_block_id].size;
                  // clang-format off
                  MatrixVectorMultiply<Eigen::Dynamic, Eigen::Dynamic, 1>(
                      values + cell.position, row_block_size, col_block_size,
                      x + col_block_pos - num_cols_e,
                      y + row_block_pos);
                  // clang-format on
                }
              });
}
