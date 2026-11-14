// u1516 – ceres::internal::DoglegStrategy::ComputeStep
// Trích từ internal/ceres/dogleg_strategy.cc, dòng 78–166 (chỉ để xem, không compile)

TrustRegionStrategy::Summary DoglegStrategy::ComputeStep(
    const TrustRegionStrategy::PerSolveOptions& per_solve_options,
    SparseMatrix* jacobian,
    const double* residuals,
    double* step) {
  CHECK(jacobian != nullptr);
  CHECK(residuals != nullptr);
  CHECK(step != nullptr);

  const int n = jacobian->num_cols();
  if (reuse_) {
    // Gauss-Newton and gradient vectors are always available, only a
    // new interpolant need to be computed. For the subspace case,
    // the subspace and the two-dimensional model are also still valid.
    switch (dogleg_type_) {
      case TRADITIONAL_DOGLEG:
        ComputeTraditionalDoglegStep(step);
        break;

      case SUBSPACE_DOGLEG:
        ComputeSubspaceDoglegStep(step);
        break;
    }
    TrustRegionStrategy::Summary summary;
    summary.num_iterations = 0;
    summary.termination_type = LinearSolverTerminationType::SUCCESS;
    return summary;
  }

  reuse_ = true;
  // Check that we have the storage needed to hold the various
  // temporary vectors.
  if (diagonal_.rows() != n) {
    diagonal_.resize(n, 1);
    gradient_.resize(n, 1);
    gauss_newton_step_.resize(n, 1);
  }

  // Vector used to form the diagonal matrix that is used to
  // regularize the Gauss-Newton solve and that defines the
  // elliptical trust region
  //
  //   || D * step || <= radius_ .
  //
  jacobian->SquaredColumnNorm(diagonal_.data());
  for (int i = 0; i < n; ++i) {
    diagonal_[i] =
        std::min(std::max(diagonal_[i], min_diagonal_), max_diagonal_);
  }
  diagonal_ = diagonal_.array().sqrt();

  ComputeGradient(jacobian, residuals);
  ComputeCauchyPoint(jacobian);

  LinearSolver::Summary linear_solver_summary =
      ComputeGaussNewtonStep(per_solve_options, jacobian, residuals);

  TrustRegionStrategy::Summary summary;
  summary.residual_norm = linear_solver_summary.residual_norm;
  summary.num_iterations = linear_solver_summary.num_iterations;
  summary.termination_type = linear_solver_summary.termination_type;

  if (linear_solver_summary.termination_type ==
      LinearSolverTerminationType::FATAL_ERROR) {
    return summary;
  }

  if (linear_solver_summary.termination_type !=
      LinearSolverTerminationType::FAILURE) {
    switch (dogleg_type_) {
      // Interpolate the Cauchy point and the Gauss-Newton step.
      case TRADITIONAL_DOGLEG:
        ComputeTraditionalDoglegStep(step);
        break;

      // Find the minimum in the subspace defined by the
      // Cauchy point and the (Gauss-)Newton step.
      case SUBSPACE_DOGLEG:
        if (!ComputeSubspaceModel(jacobian)) {
          summary.termination_type = LinearSolverTerminationType::FAILURE;
          break;
        }
        ComputeSubspaceDoglegStep(step);
        break;
    }
  }

  return summary;
}
