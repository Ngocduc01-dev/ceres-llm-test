// u1103 – ceres::internal::BlockRandomAccessSparseMatrix::SymmetricRightMultiplyAndAccumulate
// Trích từ internal/ceres/block_random_access_sparse_matrix.cc, dòng 125–163 (chỉ để xem, không compile)

void BlockRandomAccessSparseMatrix::SymmetricRightMultiplyAndAccumulate(
    const double* x, double* y) const {
  const auto bs = bsm_->block_structure();
  const auto values = bsm_->values();
  const int num_blocks = blocks_.size();

  for (int row_block_id = 0; row_block_id < num_blocks; ++row_block_id) {
    const auto& row_block = bs->rows[row_block_id];
    const int row_block_size = row_block.block.size;
    const int row_block_pos = row_block.block.position;

    for (auto& c : row_block.cells) {
      const int col_block_id = c.block_id;
      const int col_block_size = blocks_[col_block_id].size;
      const int col_block_pos = blocks_[col_block_id].position;

      MatrixVectorMultiply<Eigen::Dynamic, Eigen::Dynamic, 1>(
          values + c.position,
          row_block_size,
          col_block_size,
          x + col_block_pos,
          y + row_block_pos);
      if (col_block_id == row_block_id) {
        continue;
      }

      // Since the matrix is symmetric, but only the upper triangular
      // part is stored, if the block being accessed is not a diagonal
      // block, then use the same block to do the corresponding lower
      // triangular multiply also
      MatrixTransposeVectorMultiply<Eigen::Dynamic, Eigen::Dynamic, 1>(
          values + c.position,
          row_block_size,
          col_block_size,
          x + row_block_pos,
          y + col_block_pos);
    }
  }
}
