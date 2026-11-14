// u1406 – ceres::internal::SchurEliminator::Eliminate
// Trích từ internal/ceres/schur_eliminator_impl.h, dòng 176–304 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
void SchurEliminator<kRowBlockSize, kEBlockSize, kFBlockSize>::Eliminate(
    const BlockSparseMatrixData& A,
    const double* b,
    const double* D,
    BlockRandomAccessMatrix* lhs,
    double* rhs) {
  if (lhs->num_rows() > 0) {
    lhs->SetZero();
    if (rhs) {
      VectorRef(rhs, lhs->num_rows()).setZero();
    }
  }

  const CompressedRowBlockStructure* bs = A.block_structure();
  const int num_col_blocks = bs->cols.size();

  // Add the diagonal to the schur complement.
  if (D != nullptr) {
    ParallelFor(context_,
                num_eliminate_blocks_,
                num_col_blocks,
                num_threads_,
                [&](int i) {
                  const int block_id = i - num_eliminate_blocks_;
                  int r, c, row_stride, col_stride;
                  CellInfo* cell_info = lhs->GetCell(
                      block_id, block_id, &r, &c, &row_stride, &col_stride);
                  if (cell_info != nullptr) {
                    const int block_size = bs->cols[i].size;
                    typename EigenTypes<Eigen::Dynamic>::ConstVectorRef diag(
                        D + bs->cols[i].position, block_size);
                    MatrixRef m(cell_info->values, row_stride, col_stride);
                    m.block(r, c, block_size, block_size).diagonal() +=
                        diag.array().square().matrix();
                  }
                });
  }

  // Eliminate y blocks one chunk at a time.  For each chunk, compute
  // the entries of the normal equations and the gradient vector block
  // corresponding to the y block and then apply Gaussian elimination
  // to them. The matrix ete stores the normal matrix corresponding to
  // the block being eliminated and array buffer_ contains the
  // non-zero blocks in the row corresponding to this y block in the
  // normal equations. This computation is done in
  // ChunkDiagonalBlockAndGradient. UpdateRhs then applies gaussian
  // elimination to the rhs of the normal equations, updating the rhs
  // of the reduced linear system by modifying rhs blocks for all the
  // z blocks that share a row block/residual term with the y
  // block. EliminateRowOuterProduct does the corresponding operation
  // for the lhs of the reduced linear system.
  ParallelFor(
      context_,
      0,
      int(chunks_.size()),
      num_threads_,
      [&](int thread_id, int i) {
        double* buffer = buffer_.get() + thread_id * buffer_size_;
        const Chunk& chunk = chunks_[i];
        const int e_block_id = bs->rows[chunk.start].cells.front().block_id;
        const int e_block_size = bs->cols[e_block_id].size;

        VectorRef(buffer, buffer_size_).setZero();

        typename EigenTypes<kEBlockSize, kEBlockSize>::Matrix ete(e_block_size,
                                                                  e_block_size);

        if (D != nullptr) {
          const typename EigenTypes<kEBlockSize>::ConstVectorRef diag(
              D + bs->cols[e_block_id].position, e_block_size);
          ete = diag.array().square().matrix().asDiagonal();
        } else {
          ete.setZero();
        }

        FixedArray<double, 8> g(e_block_size);
        typename EigenTypes<kEBlockSize>::VectorRef gref(g.data(),
                                                         e_block_size);
        gref.setZero();

        // We are going to be computing
        //
        //   S += F'F - F'E(E'E)^{-1}E'F
        //
        // for each Chunk. The computation is broken down into a number of
        // function calls as below.

        // Compute the outer product of the e_blocks with themselves (ete
        // = E'E). Compute the product of the e_blocks with the
        // corresponding f_blocks (buffer = E'F), the gradient of the terms
        // in this chunk (g) and add the outer product of the f_blocks to
        // Schur complement (S += F'F).
        ChunkDiagonalBlockAndGradient(
            chunk, A, b, chunk.start, &ete, g.data(), buffer, lhs);

        // Normally one wouldn't compute the inverse explicitly, but
        // e_block_size will typically be a small number like 3, in
        // which case its much faster to compute the inverse once and
        // use it to multiply other matrices/vectors instead of doing a
        // Solve call over and over again.
        typename EigenTypes<kEBlockSize, kEBlockSize>::Matrix inverse_ete =
            InvertPSDMatrix<kEBlockSize>(assume_full_rank_ete_, ete);

        // For the current chunk compute and update the rhs of the reduced
        // linear system.
        //
        //   rhs = F'b - F'E(E'E)^(-1) E'b

        if (rhs) {
          FixedArray<double, 8> inverse_ete_g(e_block_size);
          MatrixVectorMultiply<kEBlockSize, kEBlockSize, 0>(
              inverse_ete.data(),
              e_block_size,
              e_block_size,
              g.data(),
              inverse_ete_g.data());
          UpdateRhs(chunk, A, b, chunk.start, inverse_ete_g.data(), rhs);
        }

        // S -= F'E(E'E)^{-1}E'F
        ChunkOuterProduct(
            thread_id, bs, inverse_ete, buffer, chunk.buffer_layout, lhs);
      });

  // For rows with no e_blocks, the Schur complement update reduces to
  // S += F'F.
  NoEBlockRowsUpdate(A, b, uneliminated_row_begins_, lhs, rhs);
}
