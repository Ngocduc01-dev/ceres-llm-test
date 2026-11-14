// u1117 – ceres::internal::SchurEliminator::BackSubstitute
// Trích từ internal/ceres/schur_eliminator_impl.h, dòng 306–373 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
void SchurEliminator<kRowBlockSize, kEBlockSize, kFBlockSize>::BackSubstitute(
    const BlockSparseMatrixData& A,
    const double* b,
    const double* D,
    const double* z,
    double* y) {
  const CompressedRowBlockStructure* bs = A.block_structure();
  const double* values = A.values();

  ParallelFor(context_, 0, int(chunks_.size()), num_threads_, [&](int i) {
    const Chunk& chunk = chunks_[i];
    const int e_block_id = bs->rows[chunk.start].cells.front().block_id;
    const int e_block_size = bs->cols[e_block_id].size;

    double* y_ptr = y + bs->cols[e_block_id].position;
    typename EigenTypes<kEBlockSize>::VectorRef y_block(y_ptr, e_block_size);

    typename EigenTypes<kEBlockSize, kEBlockSize>::Matrix ete(e_block_size,
                                                              e_block_size);
    if (D != nullptr) {
      const typename EigenTypes<kEBlockSize>::ConstVectorRef diag(
          D + bs->cols[e_block_id].position, e_block_size);
      ete = diag.array().square().matrix().asDiagonal();
    } else {
      ete.setZero();
    }

    for (int j = 0; j < chunk.size; ++j) {
      const CompressedRow& row = bs->rows[chunk.start + j];
      const Cell& e_cell = row.cells.front();
      DCHECK_EQ(e_block_id, e_cell.block_id);

      FixedArray<double, 8> sj(row.block.size);

      typename EigenTypes<kRowBlockSize>::VectorRef(sj.data(), row.block.size) =
          typename EigenTypes<kRowBlockSize>::ConstVectorRef(
              b + bs->rows[chunk.start + j].block.position, row.block.size);

      for (int c = 1; c < row.cells.size(); ++c) {
        const int f_block_id = row.cells[c].block_id;
        const int f_block_size = bs->cols[f_block_id].size;
        const int r_block = f_block_id - num_eliminate_blocks_;

        // clang-format off
        MatrixVectorMultiply<kRowBlockSize, kFBlockSize, -1>(
            values + row.cells[c].position, row.block.size, f_block_size,
            z + lhs_row_layout_[r_block],
            sj.data());
      }

      MatrixTransposeVectorMultiply<kRowBlockSize, kEBlockSize, 1>(
          values + e_cell.position, row.block.size, e_block_size,
          sj.data(),
          y_ptr);

      MatrixTransposeMatrixMultiply
          <kRowBlockSize, kEBlockSize, kRowBlockSize, kEBlockSize, 1>(
          values + e_cell.position, row.block.size, e_block_size,
          values + e_cell.position, row.block.size, e_block_size,
          ete.data(), 0, 0, e_block_size, e_block_size);
      // clang-format on
    }

    y_block =
        InvertPSDMatrix<kEBlockSize>(assume_full_rank_ete_, ete) * y_block;
  });
}
