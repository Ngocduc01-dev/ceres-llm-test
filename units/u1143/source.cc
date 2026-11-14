// u1143 – ceres::internal::BlockSparseJacobiPreconditioner::BlockSparseJacobiPreconditioner
// Trích từ internal/ceres/block_jacobi_preconditioner.cc, dòng 49–54 (chỉ để xem, không compile)

BlockSparseJacobiPreconditioner::BlockSparseJacobiPreconditioner(
    Preconditioner::Options options, const BlockSparseMatrix& A)
    : options_(std::move(options)) {
  m_ = std::make_unique<BlockRandomAccessDiagonalMatrix>(
      A.block_structure()->cols, options_.context, options_.num_threads);
}
