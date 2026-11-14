// u0525 – ceres::internal::DoglegStrategy::StepAccepted
// Trích từ internal/ceres/dogleg_strategy.cc, dòng 617–633 (chỉ để xem, không compile)

void DoglegStrategy::StepAccepted(double step_quality) {
  CHECK_GT(step_quality, 0.0);

  if (step_quality < decrease_threshold_) {
    radius_ *= 0.5;
  }

  if (step_quality > increase_threshold_) {
    radius_ = std::max(radius_, 3.0 * dogleg_step_norm_);
  }

  // Reduce the regularization multiplier, in the hope that whatever
  // was causing the rank deficiency has gone away and we can return
  // to doing a pure Gauss-Newton solve.
  mu_ = std::max(min_mu_, 2.0 * mu_ / mu_increase_factor_);
  reuse_ = false;
}
