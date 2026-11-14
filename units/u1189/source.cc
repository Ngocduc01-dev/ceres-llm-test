// u1189 – ceres::internal::BlockCRSJacobiPreconditioner::BlockCRSJacobiPreconditioner
// Trích từ internal/ceres/block_jacobi_preconditioner.cc, dòng 116–154 (chỉ để xem, không compile)

BlockCRSJacobiPreconditioner::BlockCRSJacobiPreconditioner(
    Preconditioner::Options options, const CompressedRowSparseMatrix& A)
    : options_(std::move(options)), locks_(A.col_blocks().size()) {
  auto& col_blocks = A.col_blocks();

  // Compute the number of non-zeros in the preconditioner. This is needed so
  // that we can construct the CompressedRowSparseMatrix.
  const int m_nnz = SumSquaredSizes(col_blocks);
  m_ = std::make_unique<CompressedRowSparseMatrix>(
      A.num_cols(), A.num_cols(), m_nnz);

  const int num_col_blocks = col_blocks.size();

  // Populate the sparsity structure of the preconditioner matrix.
  int* m_cols = m_->mutable_cols();
  int* m_rows = m_->mutable_rows();
  m_rows[0] = 0;
  for (int i = 0, idx = 0; i < num_col_blocks; ++i) {
    // For each column block populate a diagonal block in the preconditioner.
    // Not that the because of the way the CompressedRowSparseMatrix format
    // works, the entire diagonal block is laid out contiguously in memory as a
    // row-major matrix. We will use this when updating the block.
    auto& block = col_blocks[i];
    for (int j = 0; j < block.size; ++j) {
      for (int k = 0; k < block.size; ++k, ++idx) {
        m_cols[idx] = block.position + k;
      }
      m_rows[block.position + j + 1] = idx;
    }
  }

  // In reality we only need num_col_blocks locks, however that would require
  // that in UpdateImpl we are able to look up the column block from the it
  // first column. To save ourselves this map we will instead spend a few extra
  // lock objects.
  std::vector<std::mutex> locks(A.num_cols());
  locks_.swap(locks);
  CHECK_EQ(m_rows[A.num_cols()], m_nnz);
}
