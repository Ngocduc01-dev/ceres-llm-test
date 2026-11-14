// u1280 – ceres::internal::TrustRegionMinimizer::MinTrustRegionRadiusReached
// Trích từ internal/ceres/trust_region_minimizer.cc, dòng 698–714 (chỉ để xem, không compile)

bool TrustRegionMinimizer::MinTrustRegionRadiusReached() {
  if (iteration_summary_.trust_region_radius >
      options_.min_trust_region_radius) {
    return false;
  }

  solver_summary_->message = StringPrintf(
      "Minimum trust region radius reached. "
      "Trust region radius: %e <= %e",
      iteration_summary_.trust_region_radius,
      options_.min_trust_region_radius);
  solver_summary_->termination_type = CONVERGENCE;
  if (is_not_silent_) {
    VLOG(1) << "Terminating: " << solver_summary_->message;
  }
  return true;
}
