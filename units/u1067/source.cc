// u1067 – ceres::internal::TrustRegionMinimizer::ComputeCandidatePointAndEvaluateCost
// Trích từ internal/ceres/trust_region_minimizer.cc, dòng 772–790 (chỉ để xem, không compile)

void TrustRegionMinimizer::ComputeCandidatePointAndEvaluateCost() {
  if (!evaluator_->Plus(x_.data(), delta_.data(), candidate_x_.data())) {
    if (is_not_silent_) {
      LOG(WARNING) << "x_plus_delta = Plus(x, delta) failed. "
                   << "Treating it as a step with infinite cost";
    }
    candidate_cost_ = std::numeric_limits<double>::max();
    return;
  }

  if (!evaluator_->Evaluate(
          candidate_x_.data(), &candidate_cost_, nullptr, nullptr, nullptr)) {
    if (is_not_silent_) {
      LOG(WARNING) << "Step failed to evaluate. "
                   << "Treating it as a step with infinite cost";
    }
    candidate_cost_ = std::numeric_limits<double>::max();
  }
}
