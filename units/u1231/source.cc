// u1231 – ceres::internal::BlockCRSJacobiPreconditioner::UpdateImpl
// Trích từ internal/ceres/block_jacobi_preconditioner.cc, dòng 158–224 (chỉ để xem, không compile)

bool BlockCRSJacobiPreconditioner::UpdateImpl(
    const CompressedRowSparseMatrix& A, const double* D) {
  const auto& col_blocks = A.col_blocks();
  const auto& row_blocks = A.row_blocks();
  const int num_col_blocks = col_blocks.size();
  const int num_row_blocks = row_blocks.size();

  const int* a_rows = A.rows();
  const int* a_cols = A.cols();
  const double* a_values = A.values();
  double* m_values = m_->mutable_values();
  const int* m_rows = m_->rows();

  m_->SetZero();

  ParallelFor(
      options_.context,
      0,
      num_row_blocks,
      options_.num_threads,
      [this, row_blocks, a_rows, a_cols, a_values, m_values, m_rows](int i) {
        const int row = row_blocks[i].position;
        const int row_block_size = row_blocks[i].size;
        const int row_nnz = a_rows[row + 1] - a_rows[row];
        ConstMatrixRef row_block(
            a_values + a_rows[row], row_block_size, row_nnz);
        int c = 0;
        while (c < row_nnz) {
          const int idx = a_rows[row] + c;
          const int col = a_cols[idx];
          const int col_block_size = m_rows[col + 1] - m_rows[col];

          // We make use of the fact that the entire diagonal block is
          // stored contiguously in memory as a row-major matrix.
          MatrixRef m(m_values + m_rows[col], col_block_size, col_block_size);
          // We do not have a row_stride version of
          // MatrixTransposeMatrixMultiply, otherwise we could use it
          // here to further speed up the following expression.
          auto b = row_block.middleCols(c, col_block_size);
          auto lock = MakeConditionalLock(options_.num_threads, locks_[col]);
          m.noalias() += b.transpose() * b;
          c += col_block_size;
        }
      });

  ParallelFor(
      options_.context,
      0,
      num_col_blocks,
      options_.num_threads,
      [col_blocks, m_rows, m_values, D](int i) {
        const int col = col_blocks[i].position;
        const int col_block_size = col_blocks[i].size;
        MatrixRef m(m_values + m_rows[col], col_block_size, col_block_size);

        if (D != nullptr) {
          m.diagonal() +=
              ConstVectorRef(D + col, col_block_size).array().square().matrix();
        }

        // TODO(sameeragarwal): Deal with Cholesky inversion failure here and
        // elsewhere.
        m = m.llt().solve(Matrix::Identity(col_block_size, col_block_size));
      });

  return true;
}
