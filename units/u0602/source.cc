// u0602 – ceres::internal::TrustRegionMinimizer::IsStepSuccessful
// Trích từ internal/ceres/trust_region_minimizer.cc, dòng 792–818 (chỉ để xem, không compile)

bool TrustRegionMinimizer::IsStepSuccessful() {
  iteration_summary_.relative_decrease =
      step_evaluator_->StepQuality(candidate_cost_, model_cost_change_);

  // In most cases, boosting the model_cost_change by the
  // improvement caused by the inner iterations is fine, but it can
  // be the case that the original trust region step was so bad that
  // the resulting improvement in the cost was negative, and the
  // change caused by the inner iterations was large enough to
  // improve the step, but also to make relative decrease quite
  // small.
  //
  // This can cause the trust region loop to reject this step. To
  // get around this, we explicitly check if the inner iterations
  // led to a net decrease in the objective function value. If
  // they did, we accept the step even if the trust region ratio
  // is small.
  //
  // Notice that we do not just check that cost_change is positive
  // which is a weaker condition and would render the
  // min_relative_decrease threshold useless. Instead, we keep
  // track of inner_iterations_were_useful, which is true only
  // when inner iterations lead to a net decrease in the cost.
  return (inner_iterations_were_useful_ ||
          iteration_summary_.relative_decrease >
              options_.min_relative_decrease);
}
