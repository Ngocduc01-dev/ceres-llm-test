// u1273 – ceres::internal::TrustRegionMinimizer::HandleSuccessfulStep
// Trích từ internal/ceres/trust_region_minimizer.cc, dòng 823–836 (chỉ để xem, không compile)

bool TrustRegionMinimizer::HandleSuccessfulStep() {
  x_ = candidate_x_;

  // Since the step was successful, this point has already had the residual
  // evaluated (but not the jacobian). So indicate that to the evaluator.
  if (!EvaluateGradientAndJacobian(/*new_evaluation_point=*/false)) {
    return false;
  }

  iteration_summary_.step_is_successful = true;
  strategy_->StepAccepted(iteration_summary_.relative_decrease);
  step_evaluator_->StepAccepted(candidate_cost_, model_cost_change_);
  return true;
}
