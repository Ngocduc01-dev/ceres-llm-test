// u1004 – ceres::internal::LevenbergMarquardtStrategy::StepIsInvalid
// Trích từ internal/ceres/levenberg_marquardt_strategy.h, dòng 63–69 (chỉ để xem, không compile)

  void StepIsInvalid() final {
    // Treat the current step as a rejected step with no increase in
    // solution quality. Since rejected steps lead to decrease in the
    // size of the trust region, the next time ComputeStep is called,
    // this will lead to a better conditioned system.
    StepRejected(0.0);
  }
