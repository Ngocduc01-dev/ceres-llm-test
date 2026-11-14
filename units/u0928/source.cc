// u0928 – ceres::internal::TrustRegionStrategy::Create
// Trích từ internal/ceres/trust_region_strategy.cc, dòng 44–59 (chỉ để xem, không compile)

std::unique_ptr<TrustRegionStrategy> TrustRegionStrategy::Create(
    const Options& options) {
  switch (options.trust_region_strategy_type) {
    case LEVENBERG_MARQUARDT:
      return std::make_unique<LevenbergMarquardtStrategy>(options);
    case DOGLEG:
      return std::make_unique<DoglegStrategy>(options);
    default:
      LOG(FATAL) << "Unknown trust region strategy: "
                 << options.trust_region_strategy_type;
  }

  LOG(FATAL) << "Unknown trust region strategy: "
             << options.trust_region_strategy_type;
  return nullptr;
}
