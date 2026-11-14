// u1282 – ceres::internal::TrustRegionMinimizer::FunctionToleranceReached
// Trích từ internal/ceres/trust_region_minimizer.cc, dòng 742–761 (chỉ để xem, không compile)

bool TrustRegionMinimizer::FunctionToleranceReached() {
  iteration_summary_.cost_change = x_cost_ - candidate_cost_;
  const double absolute_function_tolerance =
      options_.function_tolerance * x_cost_;

  if (fabs(iteration_summary_.cost_change) > absolute_function_tolerance) {
    return false;
  }

  solver_summary_->message = StringPrintf(
      "Function tolerance reached. "
      "|cost_change|/cost: %e <= %e",
      fabs(iteration_summary_.cost_change) / x_cost_,
      options_.function_tolerance);
  solver_summary_->termination_type = CONVERGENCE;
  if (is_not_silent_) {
    VLOG(1) << "Terminating: " << solver_summary_->message;
  }
  return true;
}
