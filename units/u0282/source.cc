// u0282 – ceres::internal::DoglegStrategy::StepIsInvalid
// Trích từ internal/ceres/dogleg_strategy.cc, dòng 640–643 (chỉ để xem, không compile)

void DoglegStrategy::StepIsInvalid() {
  mu_ *= mu_increase_factor_;
  reuse_ = false;
}
