// u0943 – ceres::internal::LevenbergMarquardtStrategy::LevenbergMarquardtStrategy
// Trích từ internal/ceres/levenberg_marquardt_strategy.cc, dòng 49–64 (chỉ để xem, không compile)

LevenbergMarquardtStrategy::LevenbergMarquardtStrategy(
    const TrustRegionStrategy::Options& options)
    : linear_solver_(options.linear_solver),
      radius_(options.initial_radius),
      max_radius_(options.max_radius),
      min_diagonal_(options.min_lm_diagonal),
      max_diagonal_(options.max_lm_diagonal),
      decrease_factor_(2.0),
      reuse_diagonal_(false),
      context_(options.context),
      num_threads_(options.num_threads) {
  CHECK(linear_solver_ != nullptr);
  CHECK_GT(min_diagonal_, 0.0);
  CHECK_LE(min_diagonal_, max_diagonal_);
  CHECK_GT(max_radius_, 0.0);
}
