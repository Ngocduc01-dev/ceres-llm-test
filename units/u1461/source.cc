// u1461 – ceres::internal::IterativeSchurComplementSolver::SolveImpl
// Trích từ internal/ceres/iterative_schur_complement_solver.cc, dòng 63–156 (chỉ để xem, không compile)

LinearSolver::Summary IterativeSchurComplementSolver::SolveImpl(
    BlockSparseMatrix* A,
    const double* b,
    const LinearSolver::PerSolveOptions& per_solve_options,
    double* x) {
  EventLogger event_logger("IterativeSchurComplementSolver::Solve");

  CHECK(A->block_structure() != nullptr);
  CHECK(A->transpose_block_structure() != nullptr);

  const int num_eliminate_blocks = options_.elimination_groups[0];
  // Initialize a ImplicitSchurComplement object.
  if (schur_complement_ == nullptr) {
    DetectStructure(*(A->block_structure()),
                    num_eliminate_blocks,
                    &options_.row_block_size,
                    &options_.e_block_size,
                    &options_.f_block_size);
    schur_complement_ = std::make_unique<ImplicitSchurComplement>(options_);
  }
  schur_complement_->Init(*A, per_solve_options.D, b);

  const int num_schur_complement_blocks =
      A->block_structure()->cols.size() - num_eliminate_blocks;
  if (num_schur_complement_blocks == 0) {
    VLOG(2) << "No parameter blocks left in the schur complement.";
    LinearSolver::Summary summary;
    summary.num_iterations = 0;
    summary.termination_type = LinearSolverTerminationType::SUCCESS;
    schur_complement_->BackSubstitute(nullptr, x);
    return summary;
  }

  // Initialize the solution to the Schur complement system.
  reduced_linear_system_solution_.resize(schur_complement_->num_rows());
  reduced_linear_system_solution_.setZero();
  if (options_.use_spse_initialization) {
    Preconditioner::Options preconditioner_options(options_);
    preconditioner_options.type = SCHUR_POWER_SERIES_EXPANSION;
    PowerSeriesExpansionPreconditioner pse_solver(
        schur_complement_.get(),
        options_.max_num_spse_iterations,
        options_.spse_tolerance,
        preconditioner_options);
    pse_solver.RightMultiplyAndAccumulate(
        schur_complement_->rhs().data(),
        reduced_linear_system_solution_.data());
  }

  CreatePreconditioner(A);
  if (preconditioner_ != nullptr) {
    if (!preconditioner_->Update(*A, per_solve_options.D)) {
      LinearSolver::Summary summary;
      summary.num_iterations = 0;
      summary.termination_type = LinearSolverTerminationType::FAILURE;
      summary.message = "Preconditioner update failed.";
      return summary;
    }
  }

  ConjugateGradientsSolverOptions cg_options;
  cg_options.min_num_iterations = options_.min_num_iterations;
  cg_options.max_num_iterations = options_.max_num_iterations;
  cg_options.residual_reset_period = options_.residual_reset_period;
  cg_options.q_tolerance = per_solve_options.q_tolerance;
  cg_options.r_tolerance = per_solve_options.r_tolerance;

  LinearOperatorAdapter lhs(*schur_complement_);
  LinearOperatorAdapter preconditioner(*preconditioner_);

  Vector scratch[4];
  for (int i = 0; i < 4; ++i) {
    scratch[i].resize(schur_complement_->num_cols());
  }
  Vector* scratch_ptr[4] = {&scratch[0], &scratch[1], &scratch[2], &scratch[3]};

  event_logger.AddEvent("Setup");

  LinearSolver::Summary summary =
      ConjugateGradientsSolver(cg_options,
                               lhs,
                               schur_complement_->rhs(),
                               preconditioner,
                               scratch_ptr,
                               reduced_linear_system_solution_);

  if (summary.termination_type != LinearSolverTerminationType::FAILURE &&
      summary.termination_type != LinearSolverTerminationType::FATAL_ERROR) {
    schur_complement_->BackSubstitute(reduced_linear_system_solution_.data(),
                                      x);
  }
  event_logger.AddEvent("Solve");
  return summary;
}
