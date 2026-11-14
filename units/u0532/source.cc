// u0532 – ceres::internal::TrustRegionStepEvaluator::StepAccepted
// Trích từ internal/ceres/trust_region_step_evaluator.cc, dòng 69–111 (chỉ để xem, không compile)

void TrustRegionStepEvaluator::StepAccepted(const double cost,
                                            const double model_cost_change) {
  // Algorithm 10.1.2 from Trust Region Methods by Conn, Gould &
  // Toint.
  //
  // Step 3a
  current_cost_ = cost;
  accumulated_candidate_model_cost_change_ += model_cost_change;
  accumulated_reference_model_cost_change_ += model_cost_change;

  // Step 3b.
  if (current_cost_ < minimum_cost_) {
    minimum_cost_ = current_cost_;
    num_consecutive_nonmonotonic_steps_ = 0;
    candidate_cost_ = current_cost_;
    accumulated_candidate_model_cost_change_ = 0.0;
  } else {
    // Step 3c.
    ++num_consecutive_nonmonotonic_steps_;
    if (current_cost_ > candidate_cost_) {
      candidate_cost_ = current_cost_;
      accumulated_candidate_model_cost_change_ = 0.0;
    }
  }

  // Step 3d.
  //
  // At this point we have made too many non-monotonic steps and
  // we are going to reset the value of the reference iterate so
  // as to force the algorithm to descend.
  //
  // Note: In the original algorithm by Toint, this step was only
  // executed if the step was non-monotonic, but that would not handle
  // the case of max_consecutive_nonmonotonic_steps = 0. The small
  // modification of doing this always handles that corner case
  // correctly.
  if (num_consecutive_nonmonotonic_steps_ ==
      max_consecutive_nonmonotonic_steps_) {
    reference_cost_ = candidate_cost_;
    accumulated_reference_model_cost_change_ =
        accumulated_candidate_model_cost_change_;
  }
}
