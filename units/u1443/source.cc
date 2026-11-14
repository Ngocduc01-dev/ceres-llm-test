// u1443 – ceres::internal::SchurComplementSolver::SolveImpl
// Trích từ internal/ceres/schur_complement_solver.cc, dòng 100–158 (chỉ để xem, không compile)

LinearSolver::Summary SchurComplementSolver::SolveImpl(
    BlockSparseMatrix* A,
    const double* b,
    const LinearSolver::PerSolveOptions& per_solve_options,
    double* x) {
  EventLogger event_logger("SchurComplementSolver::Solve");

  const CompressedRowBlockStructure* bs = A->block_structure();
  if (eliminator_ == nullptr) {
    const int num_eliminate_blocks = options_.elimination_groups[0];
    const int num_f_blocks = bs->cols.size() - num_eliminate_blocks;

    InitStorage(bs);
    DetectStructure(*bs,
                    num_eliminate_blocks,
                    &options_.row_block_size,
                    &options_.e_block_size,
                    &options_.f_block_size);

    // For the special case of the static structure <2,3,6> with
    // exactly one f block use the SchurEliminatorForOneFBlock.
    //
    // TODO(sameeragarwal): A more scalable template specialization
    // mechanism that does not cause binary bloat.
    if (options_.row_block_size == 2 && options_.e_block_size == 3 &&
        options_.f_block_size == 6 && num_f_blocks == 1) {
      eliminator_ = std::make_unique<SchurEliminatorForOneFBlock<2, 3, 6>>();
    } else {
      eliminator_ = SchurEliminatorBase::Create(options_);
    }

    CHECK(eliminator_);
    const bool kFullRankETE = true;
    eliminator_->Init(num_eliminate_blocks, kFullRankETE, bs);
  }

  std::fill(x, x + A->num_cols(), 0.0);
  event_logger.AddEvent("Setup");

  eliminator_->Eliminate(BlockSparseMatrixData(*A),
                         b,
                         per_solve_options.D,
                         lhs_.get(),
                         rhs_.data());
  event_logger.AddEvent("Eliminate");

  double* reduced_solution = x + A->num_cols() - lhs_->num_cols();
  const LinearSolver::Summary summary =
      SolveReducedLinearSystem(per_solve_options, reduced_solution);
  event_logger.AddEvent("ReducedSolve");

  if (summary.termination_type == LinearSolverTerminationType::SUCCESS) {
    eliminator_->BackSubstitute(
        BlockSparseMatrixData(*A), b, per_solve_options.D, reduced_solution, x);
    event_logger.AddEvent("BackSubstitute");
  }

  return summary;
}
