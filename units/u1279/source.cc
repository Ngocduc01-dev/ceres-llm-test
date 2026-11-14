// u1279 – ceres::internal::TrustRegionMinimizer::MaxSolverIterationsReached
// Trích từ internal/ceres/trust_region_minimizer.cc, dòng 660–675 (chỉ để xem, không compile)

bool TrustRegionMinimizer::MaxSolverIterationsReached() {
  if (iteration_summary_.iteration < options_.max_num_iterations) {
    return false;
  }

  solver_summary_->message = StringPrintf(
      "Maximum number of iterations reached. "
      "Number of iterations: %d.",
      iteration_summary_.iteration);

  solver_summary_->termination_type = NO_CONVERGENCE;
  if (is_not_silent_) {
    VLOG(1) << "Terminating: " << solver_summary_->message;
  }
  return true;
}
