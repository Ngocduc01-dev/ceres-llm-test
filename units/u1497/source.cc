// u1497 – ceres::internal::DoglegStrategy::ComputeGaussNewtonStep
// Trích từ internal/ceres/dogleg_strategy.cc, dòng 516–615 (chỉ để xem, không compile)

LinearSolver::Summary DoglegStrategy::ComputeGaussNewtonStep(
    const PerSolveOptions& per_solve_options,
    SparseMatrix* jacobian,
    const double* residuals) {
  const int n = jacobian->num_cols();
  LinearSolver::Summary linear_solver_summary;
  linear_solver_summary.termination_type = LinearSolverTerminationType::FAILURE;

  // The Jacobian matrix is often quite poorly conditioned. Thus it is
  // necessary to add a diagonal matrix at the bottom to prevent the
  // linear solver from failing.
  //
  // We do this by computing the same diagonal matrix as the one used
  // by Levenberg-Marquardt (other choices are possible), and scaling
  // it by a small constant (independent of the trust region radius).
  //
  // If the solve fails, the multiplier to the diagonal is increased
  // up to max_mu_ by a factor of mu_increase_factor_ every time. If
  // the linear solver is still not successful, the strategy returns
  // with LinearSolverTerminationType::FAILURE.
  //
  // Next time when a new Gauss-Newton step is requested, the
  // multiplier starts out from the last successful solve.
  //
  // When a step is declared successful, the multiplier is decreased
  // by half of mu_increase_factor_.

  while (mu_ < max_mu_) {
    // Dogleg, as far as I (sameeragarwal) understand it, requires a
    // reasonably good estimate of the Gauss-Newton step. This means
    // that we need to solve the normal equations more or less
    // exactly. This is reflected in the values of the tolerances set
    // below.
    //
    // For now, this strategy should only be used with exact
    // factorization based solvers, for which these tolerances are
    // automatically satisfied.
    //
    // The right way to combine inexact solves with trust region
    // methods is to use Stiehaug's method.
    LinearSolver::PerSolveOptions solve_options;
    solve_options.q_tolerance = 0.0;
    solve_options.r_tolerance = 0.0;

    lm_diagonal_ = diagonal_ * std::sqrt(mu_);
    solve_options.D = lm_diagonal_.data();

    // As in the LevenbergMarquardtStrategy, solve Jy = r instead
    // of Jx = -r and later set x = -y to avoid having to modify
    // either jacobian or residuals.
    InvalidateArray(n, gauss_newton_step_.data());
    linear_solver_summary = linear_solver_->Solve(
        jacobian, residuals, solve_options, gauss_newton_step_.data());

    if (per_solve_options.dump_format_type == CONSOLE ||
        (per_solve_options.dump_format_type != CONSOLE &&
         !per_solve_options.dump_filename_base.empty())) {
      if (!DumpLinearLeastSquaresProblem(per_solve_options.dump_filename_base,
                                         per_solve_options.dump_format_type,
                                         jacobian,
                                         solve_options.D,
                                         residuals,
                                         gauss_newton_step_.data(),
                                         0)) {
        LOG(ERROR) << "Unable to dump trust region problem."
                   << " Filename base: "
                   << per_solve_options.dump_filename_base;
      }
    }

    if (linear_solver_summary.termination_type ==
        LinearSolverTerminationType::FATAL_ERROR) {
      return linear_solver_summary;
    }

    if (linear_solver_summary.termination_type ==
            LinearSolverTerminationType::FAILURE ||
        !IsArrayValid(n, gauss_newton_step_.data())) {
      mu_ *= mu_increase_factor_;
      VLOG(2) << "Increasing mu " << mu_;
      linear_solver_summary.termination_type =
          LinearSolverTerminationType::FAILURE;
      continue;
    }
    break;
  }

  if (linear_solver_summary.termination_type !=
      LinearSolverTerminationType::FAILURE) {
    // The scaled Gauss-Newton step is D * GN:
    //
    //     - (D^-1 J^T J D^-1)^-1 (D^-1 g)
    //   = - D (J^T J)^-1 D D^-1 g
    //   = D -(J^T J)^-1 g
    //
    gauss_newton_step_.array() *= -diagonal_.array();
  }

  return linear_solver_summary;
}
