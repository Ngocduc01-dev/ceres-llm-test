// u0467 – ceres::internal::LevenbergMarquardtStrategy::StepAccepted
// Trích từ internal/ceres/levenberg_marquardt_strategy.cc, dòng 157–164 (chỉ để xem, không compile)

void LevenbergMarquardtStrategy::StepAccepted(double step_quality) {
  CHECK_GT(step_quality, 0.0);
  radius_ =
      radius_ / std::max(1.0 / 3.0, 1.0 - pow(2.0 * step_quality - 1.0, 3));
  radius_ = std::min(max_radius_, radius_);
  decrease_factor_ = 2.0;
  reuse_diagonal_ = false;
}
