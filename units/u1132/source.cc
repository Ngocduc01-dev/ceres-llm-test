// u1132 – ceres::internal::DenseSchurComplementSolver::InitStorage
// Trích từ internal/ceres/schur_complement_solver.cc, dòng 168–176 (chỉ để xem, không compile)

void DenseSchurComplementSolver::InitStorage(
    const CompressedRowBlockStructure* bs) {
  const int num_eliminate_blocks = options().elimination_groups[0];
  const int num_col_blocks = bs->cols.size();
  auto blocks = Tail(bs->cols, num_col_blocks - num_eliminate_blocks);
  set_lhs(std::make_unique<BlockRandomAccessDenseMatrix>(
      blocks, options().context, options().num_threads));
  ResizeRhs(lhs()->num_rows());
}
