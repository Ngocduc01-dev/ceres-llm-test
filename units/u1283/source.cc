// u1283 – ceres::internal::TrustRegionMinimizer::GradientToleranceReached
// Trích từ internal/ceres/trust_region_minimizer.cc, dòng 679–695 (chỉ để xem, không compile)

bool TrustRegionMinimizer::GradientToleranceReached() {
  if (!iteration_summary_.step_is_successful ||
      iteration_summary_.gradient_max_norm > options_.gradient_tolerance) {
    return false;
  }

  solver_summary_->message = StringPrintf(
      "Gradient tolerance reached. "
      "Gradient max norm: %e <= %e",
      iteration_summary_.gradient_max_norm,
      options_.gradient_tolerance);
  solver_summary_->termination_type = CONVERGENCE;
  if (is_not_silent_) {
    VLOG(1) << "Terminating: " << solver_summary_->message;
  }
  return true;
}
