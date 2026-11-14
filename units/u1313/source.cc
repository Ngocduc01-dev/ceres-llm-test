// u1313 – ceres::internal::SchurEliminator::ChunkDiagonalBlockAndGradient
// Trích từ internal/ceres/schur_eliminator_impl.h, dòng 441–505 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
void SchurEliminator<kRowBlockSize, kEBlockSize, kFBlockSize>::
    ChunkDiagonalBlockAndGradient(
        const Chunk& chunk,
        const BlockSparseMatrixData& A,
        const double* b,
        int row_block_counter,
        typename EigenTypes<kEBlockSize, kEBlockSize>::Matrix* ete,
        double* g,
        double* buffer,
        BlockRandomAccessMatrix* lhs) {
  const CompressedRowBlockStructure* bs = A.block_structure();
  const double* values = A.values();

  int b_pos = bs->rows[row_block_counter].block.position;
  const int e_block_size = ete->rows();

  // Iterate over the rows in this chunk, for each row, compute the
  // contribution of its F blocks to the Schur complement, the
  // contribution of its E block to the matrix EE' (ete), and the
  // corresponding block in the gradient vector.
  for (int j = 0; j < chunk.size; ++j) {
    const CompressedRow& row = bs->rows[row_block_counter + j];

    if (row.cells.size() > 1) {
      EBlockRowOuterProduct(A, row_block_counter + j, lhs);
    }

    // Extract the e_block, ETE += E_i' E_i
    const Cell& e_cell = row.cells.front();
    // clang-format off
    MatrixTransposeMatrixMultiply
        <kRowBlockSize, kEBlockSize, kRowBlockSize, kEBlockSize, 1>(
            values + e_cell.position, row.block.size, e_block_size,
            values + e_cell.position, row.block.size, e_block_size,
            ete->data(), 0, 0, e_block_size, e_block_size);
    // clang-format on

    if (b) {
      // g += E_i' b_i
      // clang-format off
      MatrixTransposeVectorMultiply<kRowBlockSize, kEBlockSize, 1>(
          values + e_cell.position, row.block.size, e_block_size,
          b + b_pos,
          g);
      // clang-format on
    }

    // buffer = E'F. This computation is done by iterating over the
    // f_blocks for each row in the chunk.
    for (int c = 1; c < row.cells.size(); ++c) {
      const int f_block_id = row.cells[c].block_id;
      const int f_block_size = bs->cols[f_block_id].size;
      double* buffer_ptr = buffer + FindOrDie(chunk.buffer_layout, f_block_id);
      // clang-format off
      MatrixTransposeMatrixMultiply
          <kRowBlockSize, kEBlockSize, kRowBlockSize, kFBlockSize, 1>(
          values + e_cell.position, row.block.size, e_block_size,
          values + row.cells[c].position, row.block.size, f_block_size,
          buffer_ptr, 0, 0, e_block_size, f_block_size);
      // clang-format on
    }
    b_pos += row.block.size;
  }
}
