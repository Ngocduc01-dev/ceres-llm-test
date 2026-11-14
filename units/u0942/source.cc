// u0942 – ceres::internal::DoglegStrategy::DoglegStrategy
// Trích từ internal/ceres/dogleg_strategy.cc, dòng 53–72 (chỉ để xem, không compile)

DoglegStrategy::DoglegStrategy(const TrustRegionStrategy::Options& options)
    : linear_solver_(options.linear_solver),
      radius_(options.initial_radius),
      max_radius_(options.max_radius),
      min_diagonal_(options.min_lm_diagonal),
      max_diagonal_(options.max_lm_diagonal),
      mu_(kMinMu),
      min_mu_(kMinMu),
      max_mu_(kMaxMu),
      mu_increase_factor_(10.0),
      increase_threshold_(0.75),
      decrease_threshold_(0.25),
      dogleg_step_norm_(0.0),
      reuse_(false),
      dogleg_type_(options.dogleg_type) {
  CHECK(linear_solver_ != nullptr);
  CHECK_GT(min_diagonal_, 0.0);
  CHECK_LE(min_diagonal_, max_diagonal_);
  CHECK_GT(max_radius_, 0.0);
}
