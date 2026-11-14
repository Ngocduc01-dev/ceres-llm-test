// u1441 – ceres::internal::CgnrSolver::SolveImpl
// Trích từ internal/ceres/cgnr_solver.cc, dòng 145–206 (chỉ để xem, không compile)

LinearSolver::Summary CgnrSolver::SolveImpl(
    BlockSparseMatrix* A,
    const double* b,
    const LinearSolver::PerSolveOptions& per_solve_options,
    double* x) {
  EventLogger event_logger("CgnrSolver::Solve");
  if (!preconditioner_) {
    Preconditioner::Options preconditioner_options;
    preconditioner_options.type = options_.preconditioner_type;
    preconditioner_options.subset_preconditioner_start_row_block =
        options_.subset_preconditioner_start_row_block;
    preconditioner_options.sparse_linear_algebra_library_type =
        options_.sparse_linear_algebra_library_type;
    preconditioner_options.ordering_type = options_.ordering_type;
    preconditioner_options.num_threads = options_.num_threads;
    preconditioner_options.context = options_.context;

    if (options_.preconditioner_type == JACOBI) {
      preconditioner_ = std::make_unique<BlockSparseJacobiPreconditioner>(
          preconditioner_options, *A);
    } else if (options_.preconditioner_type == SUBSET) {
      preconditioner_ =
          std::make_unique<SubsetPreconditioner>(preconditioner_options, *A);
    } else {
      preconditioner_ = std::make_unique<IdentityPreconditioner>(A->num_cols());
    }
  }
  preconditioner_->Update(*A, per_solve_options.D);

  ConjugateGradientsSolverOptions cg_options;
  cg_options.min_num_iterations = options_.min_num_iterations;
  cg_options.max_num_iterations = options_.max_num_iterations;
  cg_options.residual_reset_period = options_.residual_reset_period;
  cg_options.q_tolerance = per_solve_options.q_tolerance;
  cg_options.r_tolerance = per_solve_options.r_tolerance;
  cg_options.context = options_.context;
  cg_options.num_threads = options_.num_threads;

  // lhs = AtA + DtD
  CgnrLinearOperator lhs(
      *A, per_solve_options.D, options_.context, options_.num_threads);
  // rhs = Atb.
  Vector rhs(A->num_cols());
  rhs.setZero();
  A->LeftMultiplyAndAccumulate(
      b, rhs.data(), options_.context, options_.num_threads);

  cg_solution_ = Vector::Zero(A->num_cols());
  for (int i = 0; i < 4; ++i) {
    if (scratch_[i] == nullptr) {
      scratch_[i] = new Vector(A->num_cols());
    }
  }
  event_logger.AddEvent("Setup");

  LinearOperatorAdapter preconditioner(*preconditioner_);
  auto summary = ConjugateGradientsSolver(
      cg_options, lhs, rhs, preconditioner, scratch_, cg_solution_);
  VectorRef(x, A->num_cols()) = cg_solution_;
  event_logger.AddEvent("Solve");
  return summary;
}
