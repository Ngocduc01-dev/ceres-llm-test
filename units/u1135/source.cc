// u1135 – ceres::internal::SchurEliminator::UpdateRhs
// Trích từ internal/ceres/schur_eliminator_impl.h, dòng 378–420 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
void SchurEliminator<kRowBlockSize, kEBlockSize, kFBlockSize>::UpdateRhs(
    const Chunk& chunk,
    const BlockSparseMatrixData& A,
    const double* b,
    int row_block_counter,
    const double* inverse_ete_g,
    double* rhs) {
  const CompressedRowBlockStructure* bs = A.block_structure();
  const double* values = A.values();

  const int e_block_id = bs->rows[chunk.start].cells.front().block_id;
  const int e_block_size = bs->cols[e_block_id].size;
  int b_pos = bs->rows[row_block_counter].block.position;
  for (int j = 0; j < chunk.size; ++j) {
    const CompressedRow& row = bs->rows[row_block_counter + j];
    const Cell& e_cell = row.cells.front();

    typename EigenTypes<kRowBlockSize>::Vector sj =
        typename EigenTypes<kRowBlockSize>::ConstVectorRef(b + b_pos,
                                                           row.block.size);

    // clang-format off
    MatrixVectorMultiply<kRowBlockSize, kEBlockSize, -1>(
        values + e_cell.position, row.block.size, e_block_size,
        inverse_ete_g, sj.data());
    // clang-format on

    for (int c = 1; c < row.cells.size(); ++c) {
      const int block_id = row.cells[c].block_id;
      const int block_size = bs->cols[block_id].size;
      const int block = block_id - num_eliminate_blocks_;
      auto lock = MakeConditionalLock(num_threads_, *rhs_locks_[block]);
      // clang-format off
      MatrixTransposeVectorMultiply<kRowBlockSize, kFBlockSize, 1>(
          values + row.cells[c].position,
          row.block.size, block_size,
          sj.data(), rhs + lhs_row_layout_[block]);
      // clang-format on
    }
    b_pos += row.block.size;
  }
}
