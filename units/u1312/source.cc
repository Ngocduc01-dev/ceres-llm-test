// u1312 – ceres::internal::SchurEliminator::NoEBlockRowsUpdate
// Trích từ internal/ceres/schur_eliminator_impl.h, dòng 566–593 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
void SchurEliminator<kRowBlockSize, kEBlockSize, kFBlockSize>::
    NoEBlockRowsUpdate(const BlockSparseMatrixData& A,
                       const double* b,
                       int row_block_counter,
                       BlockRandomAccessMatrix* lhs,
                       double* rhs) {
  const CompressedRowBlockStructure* bs = A.block_structure();
  const double* values = A.values();
  for (; row_block_counter < bs->rows.size(); ++row_block_counter) {
    NoEBlockRowOuterProduct(A, row_block_counter, lhs);
    if (!rhs) {
      continue;
    }
    const CompressedRow& row = bs->rows[row_block_counter];
    for (int c = 0; c < row.cells.size(); ++c) {
      const int block_id = row.cells[c].block_id;
      const int block_size = bs->cols[block_id].size;
      const int block = block_id - num_eliminate_blocks_;
      // clang-format off
      MatrixTransposeVectorMultiply<Eigen::Dynamic, Eigen::Dynamic, 1>(
          values + row.cells[c].position, row.block.size, block_size,
          b + row.block.position,
          rhs + lhs_row_layout_[block]);
      // clang-format on
    }
  }
}
