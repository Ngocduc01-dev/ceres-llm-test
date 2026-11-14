// u1489 – ceres::internal::LevenbergMarquardtStrategy::ComputeStep
// Trích từ internal/ceres/levenberg_marquardt_strategy.cc, dòng 68–155 (chỉ để xem, không compile)

TrustRegionStrategy::Summary LevenbergMarquardtStrategy::ComputeStep(
    const TrustRegionStrategy::PerSolveOptions& per_solve_options,
    SparseMatrix* jacobian,
    const double* residuals,
    double* step) {
  CHECK(jacobian != nullptr);
  CHECK(residuals != nullptr);
  CHECK(step != nullptr);

  const int num_parameters = jacobian->num_cols();
  if (!reuse_diagonal_) {
    if (diagonal_.rows() != num_parameters) {
      diagonal_.resize(num_parameters, 1);
    }

    jacobian->SquaredColumnNorm(diagonal_.data(), context_, num_threads_);
    ParallelAssign(context_,
                   num_threads_,
                   diagonal_,
                   diagonal_.array().max(min_diagonal_).min(max_diagonal_));
  }

  if (lm_diagonal_.size() == 0) {
    lm_diagonal_.resize(num_parameters);
  }
  ParallelAssign(
      context_, num_threads_, lm_diagonal_, (diagonal_ / radius_).cwiseSqrt());

  LinearSolver::PerSolveOptions solve_options;
  solve_options.D = lm_diagonal_.data();
  solve_options.q_tolerance = per_solve_options.eta;
  // Disable r_tolerance checking. Since we only care about
  // termination via the q_tolerance. As Nash and Sofer show,
  // r_tolerance based termination is essentially useless in
  // Truncated Newton methods.
  solve_options.r_tolerance = -1.0;

  // Invalidate the output array lm_step, so that we can detect if
  // the linear solver generated numerical garbage.  This is known
  // to happen for the DENSE_QR and then DENSE_SCHUR solver when
  // the Jacobian is severely rank deficient and mu is too small.
  InvalidateArray(num_parameters, step);

  // Instead of solving Jx = -r, solve Jy = r.
  // Then x can be found as x = -y, but the inputs jacobian and residuals
  // do not need to be modified.
  LinearSolver::Summary linear_solver_summary =
      linear_solver_->Solve(jacobian, residuals, solve_options, step);

  if (linear_solver_summary.termination_type ==
      LinearSolverTerminationType::FATAL_ERROR) {
    LOG(WARNING) << "Linear solver fatal error: "
                 << linear_solver_summary.message;
  } else if (linear_solver_summary.termination_type ==
             LinearSolverTerminationType::FAILURE) {
    LOG(WARNING) << "Linear solver failure. Failed to compute a step: "
                 << linear_solver_summary.message;
  } else if (!IsArrayValid(num_parameters, step)) {
    LOG(WARNING) << "Linear solver failure. Failed to compute a finite step.";
    linear_solver_summary.termination_type =
        LinearSolverTerminationType::FAILURE;
  } else {
    VectorRef step_vec(step, num_parameters);
    ParallelAssign(context_, num_threads_, step_vec, -step_vec);
  }
  reuse_diagonal_ = true;

  if (per_solve_options.dump_format_type == CONSOLE ||
      (per_solve_options.dump_format_type != CONSOLE &&
       !per_solve_options.dump_filename_base.empty())) {
    if (!DumpLinearLeastSquaresProblem(per_solve_options.dump_filename_base,
                                       per_solve_options.dump_format_type,
                                       jacobian,
                                       solve_options.D,
                                       residuals,
                                       step,
                                       0)) {
      LOG(ERROR) << "Unable to dump trust region problem."
                 << " Filename base: " << per_solve_options.dump_filename_base;
    }
  }

  TrustRegionStrategy::Summary summary;
  summary.residual_norm = linear_solver_summary.residual_norm;
  summary.num_iterations = linear_solver_summary.num_iterations;
  summary.termination_type = linear_solver_summary.termination_type;
  return summary;
}
