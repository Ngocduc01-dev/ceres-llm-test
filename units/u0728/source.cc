// u0728 – ceres::internal::Preprocessor::Create
// Trích từ internal/ceres/preprocessor.cc, dòng 45–57 (chỉ để xem, không compile)

std::unique_ptr<Preprocessor> Preprocessor::Create(
    MinimizerType minimizer_type) {
  if (minimizer_type == TRUST_REGION) {
    return std::make_unique<TrustRegionPreprocessor>();
  }

  if (minimizer_type == LINE_SEARCH) {
    return std::make_unique<LineSearchPreprocessor>();
  }

  LOG(FATAL) << "Unknown minimizer_type: " << minimizer_type;
  return nullptr;
}
