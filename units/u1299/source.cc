// u1299 – ceres::internal::SchurJacobiPreconditioner::SchurJacobiPreconditioner
// Trích từ internal/ceres/schur_jacobi_preconditioner.cc, dòng 45–66 (chỉ để xem, không compile)

SchurJacobiPreconditioner::SchurJacobiPreconditioner(
    const CompressedRowBlockStructure& bs, Preconditioner::Options options)
    : options_(std::move(options)) {
  CHECK_GT(options_.elimination_groups.size(), 1);
  CHECK_GT(options_.elimination_groups[0], 0);
  const int num_blocks = bs.cols.size() - options_.elimination_groups[0];
  CHECK_GT(num_blocks, 0) << "Jacobian should have at least 1 f_block for "
                          << "SCHUR_JACOBI preconditioner.";
  CHECK(options_.context != nullptr);

  std::vector<Block> blocks(num_blocks);
  int position = 0;
  for (int i = 0; i < num_blocks; ++i) {
    blocks[i] =
        Block(bs.cols[i + options_.elimination_groups[0]].size, position);
    position += blocks[i].size;
  }

  m_ = std::make_unique<BlockRandomAccessDiagonalMatrix>(
      blocks, options_.context, options_.num_threads);
  InitEliminator(bs);
}
