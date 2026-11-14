// u0921 – ceres::internal::Minimizer::Create
// Trích từ internal/ceres/minimizer.cc, dòng 42–53 (chỉ để xem, không compile)

std::unique_ptr<Minimizer> Minimizer::Create(MinimizerType minimizer_type) {
  if (minimizer_type == TRUST_REGION) {
    return std::make_unique<TrustRegionMinimizer>();
  }

  if (minimizer_type == LINE_SEARCH) {
    return std::make_unique<LineSearchMinimizer>();
  }

  LOG(FATAL) << "Unknown minimizer_type: " << minimizer_type;
  return nullptr;
}
