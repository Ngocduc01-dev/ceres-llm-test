// u1281 – ceres::internal::TrustRegionMinimizer::ParameterToleranceReached
// Trích từ internal/ceres/trust_region_minimizer.cc, dòng 717–739 (chỉ để xem, không compile)

bool TrustRegionMinimizer::ParameterToleranceReached() {
  const double x_norm = x_.norm();

  // Compute the norm of the step in the ambient space.
  iteration_summary_.step_norm = (x_ - candidate_x_).norm();
  const double step_size_tolerance =
      options_.parameter_tolerance * (x_norm + options_.parameter_tolerance);

  if (iteration_summary_.step_norm > step_size_tolerance) {
    return false;
  }

  solver_summary_->message = StringPrintf(
      "Parameter tolerance reached. "
      "Relative step_norm: %e <= %e.",
      (iteration_summary_.step_norm / (x_norm + options_.parameter_tolerance)),
      options_.parameter_tolerance);
  solver_summary_->termination_type = CONVERGENCE;
  if (is_not_silent_) {
    VLOG(1) << "Terminating: " << solver_summary_->message;
  }
  return true;
}
