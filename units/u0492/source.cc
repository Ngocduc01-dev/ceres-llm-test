// u0492 – ceres::internal::TrustRegionStepEvaluator::StepQuality
// Trích từ internal/ceres/trust_region_step_evaluator.cc, dòng 51–67 (chỉ để xem, không compile)

double TrustRegionStepEvaluator::StepQuality(
    const double cost, const double model_cost_change) const {
  // If the function evaluation for this step was a failure, in which
  // case the TrustRegionMinimizer would have set the cost to
  // std::numeric_limits<double>::max(). In this case, the division by
  // model_cost_change can result in an overflow. To prevent that from
  // happening, we will deal with this case explicitly.
  if (cost >= std::numeric_limits<double>::max()) {
    return std::numeric_limits<double>::lowest();
  }

  const double relative_decrease = (current_cost_ - cost) / model_cost_change;
  const double historical_relative_decrease =
      (reference_cost_ - cost) /
      (accumulated_reference_model_cost_change_ + model_cost_change);
  return std::max(relative_decrease, historical_relative_decrease);
}
