// u1278 – ceres::internal::TrustRegionMinimizer::MaxSolverTimeReached
// Trích từ internal/ceres/trust_region_minimizer.cc, dòng 637–655 (chỉ để xem, không compile)

bool TrustRegionMinimizer::MaxSolverTimeReached() {
  const double total_solver_time =
      WallTimeInSeconds() - start_time_in_secs_ +
      solver_summary_->preprocessor_time_in_seconds;
  if (total_solver_time < options_.max_solver_time_in_seconds) {
    return false;
  }

  solver_summary_->message = StringPrintf(
      "Maximum solver time reached. "
      "Total solver time: %e >= %e.",
      total_solver_time,
      options_.max_solver_time_in_seconds);
  solver_summary_->termination_type = NO_CONVERGENCE;
  if (is_not_silent_) {
    VLOG(1) << "Terminating: " << solver_summary_->message;
  }
  return true;
}
