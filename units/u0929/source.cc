// u0929 – ceres::internal::BlockSparseMatrix::RightMultiplyAndAccumulate
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 238–273 (chỉ để xem, không compile)

void BlockSparseMatrix::RightMultiplyAndAccumulate(const double* x,
                                                   double* y,
                                                   ContextImpl* context,
                                                   int num_threads) const {
  CHECK(x != nullptr);
  CHECK(y != nullptr);

  const auto values = values_;
  const auto block_structure = block_structure_.get();
  const auto num_row_blocks = block_structure->rows.size();

  ParallelFor(context,
              0,
              num_row_blocks,
              num_threads,
              [values, block_structure, x, y](int row_block_id) {
                const int row_block_pos =
                    block_structure->rows[row_block_id].block.position;
                const int row_block_size =
                    block_structure->rows[row_block_id].block.size;
                const auto& cells = block_structure->rows[row_block_id].cells;
                for (const auto& cell : cells) {
                  const int col_block_id = cell.block_id;
                  const int col_block_size =
                      block_structure->cols[col_block_id].size;
                  const int col_block_pos =
                      block_structure->cols[col_block_id].position;
                  MatrixVectorMultiply<Eigen::Dynamic, Eigen::Dynamic, 1>(
                      values + cell.position,
                      row_block_size,
                      col_block_size,
                      x + col_block_pos,
                      y + row_block_pos);
                }
              });
}
