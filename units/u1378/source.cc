// u1378 – ceres::internal::SparseSchurComplementSolver::SolveReducedLinearSystemUsingConjugateGradients
// Trích từ internal/ceres/schur_complement_solver.cc, dòng 335–406 (chỉ để xem, không compile)

LinearSolver::Summary
SparseSchurComplementSolver::SolveReducedLinearSystemUsingConjugateGradients(
    const LinearSolver::PerSolveOptions& per_solve_options, double* solution) {
  CHECK(options().use_explicit_schur_complement);
  const int num_rows = lhs()->num_rows();
  // The case where there are no f blocks, and the system is block
  // diagonal.
  if (num_rows == 0) {
    LinearSolver::Summary summary;
    summary.num_iterations = 0;
    summary.termination_type = LinearSolverTerminationType::SUCCESS;
    summary.message = "Success.";
    return summary;
  }

  // Only SCHUR_JACOBI is supported over here right now.
  CHECK_EQ(options().preconditioner_type, SCHUR_JACOBI);

  if (preconditioner_ == nullptr) {
    preconditioner_ = std::make_unique<BlockRandomAccessDiagonalMatrix>(
        blocks_, options().context, options().num_threads);
  }

  auto* sc = down_cast<BlockRandomAccessSparseMatrix*>(mutable_lhs());

  // Extract block diagonal from the Schur complement to construct the
  // schur_jacobi preconditioner.
  for (int i = 0; i < blocks_.size(); ++i) {
    const int block_size = blocks_[i].size;

    int sc_r, sc_c, sc_row_stride, sc_col_stride;
    CellInfo* sc_cell_info =
        sc->GetCell(i, i, &sc_r, &sc_c, &sc_row_stride, &sc_col_stride);
    CHECK(sc_cell_info != nullptr);
    MatrixRef sc_m(sc_cell_info->values, sc_row_stride, sc_col_stride);

    int pre_r, pre_c, pre_row_stride, pre_col_stride;
    CellInfo* pre_cell_info = preconditioner_->GetCell(
        i, i, &pre_r, &pre_c, &pre_row_stride, &pre_col_stride);
    CHECK(pre_cell_info != nullptr);
    MatrixRef pre_m(pre_cell_info->values, pre_row_stride, pre_col_stride);

    pre_m.block(pre_r, pre_c, block_size, block_size) =
        sc_m.block(sc_r, sc_c, block_size, block_size);
  }
  preconditioner_->Invert();

  VectorRef(solution, num_rows).setZero();

  auto lhs = std::make_unique<BlockRandomAccessSparseMatrixAdapter>(*sc);
  auto preconditioner =
      std::make_unique<BlockRandomAccessDiagonalMatrixAdapter>(
          *preconditioner_);

  ConjugateGradientsSolverOptions cg_options;
  cg_options.min_num_iterations = options().min_num_iterations;
  cg_options.max_num_iterations = options().max_num_iterations;
  cg_options.residual_reset_period = options().residual_reset_period;
  cg_options.q_tolerance = per_solve_options.q_tolerance;
  cg_options.r_tolerance = per_solve_options.r_tolerance;

  cg_solution_ = Vector::Zero(sc->num_rows());
  for (int i = 0; i < 4; ++i) {
    if (scratch_[i] == nullptr) {
      scratch_[i] = new Vector(sc->num_rows());
    }
  }
  auto summary = ConjugateGradientsSolver<Vector>(
      cg_options, *lhs, rhs(), *preconditioner, scratch_, cg_solution_);
  VectorRef(solution, sc->num_rows()) = cg_solution_;
  return summary;
}
