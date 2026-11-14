// u0281 – ceres::internal::DoglegStrategy::StepRejected
// Trích từ internal/ceres/dogleg_strategy.cc, dòng 635–638 (chỉ để xem, không compile)

void DoglegStrategy::StepRejected(double /*step_quality*/) {
  radius_ *= 0.5;
  reuse_ = true;
}
