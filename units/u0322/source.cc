// u0322 – ceres::internal::LevenbergMarquardtStrategy::StepRejected
// Trích từ internal/ceres/levenberg_marquardt_strategy.cc, dòng 166–170 (chỉ để xem, không compile)

void LevenbergMarquardtStrategy::StepRejected(double /*step_quality*/) {
  radius_ = radius_ / decrease_factor_;
  decrease_factor_ *= 2.0;
  reuse_diagonal_ = true;
}
