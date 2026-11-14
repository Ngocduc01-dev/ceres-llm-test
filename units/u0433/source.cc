// u0433 – ceres::internal::TrustRegionStepEvaluator::TrustRegionStepEvaluator
// Trích từ internal/ceres/trust_region_step_evaluator.cc, dòng 40–49 (chỉ để xem, không compile)

TrustRegionStepEvaluator::TrustRegionStepEvaluator(
    const double initial_cost, const int max_consecutive_nonmonotonic_steps)
    : max_consecutive_nonmonotonic_steps_(max_consecutive_nonmonotonic_steps),
      minimum_cost_(initial_cost),
      current_cost_(initial_cost),
      reference_cost_(initial_cost),
      candidate_cost_(initial_cost),
      accumulated_reference_model_cost_change_(0.0),
      accumulated_candidate_model_cost_change_(0.0),
      num_consecutive_nonmonotonic_steps_(0) {}
