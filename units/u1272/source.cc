// u1272 – ceres::internal::TrustRegionMinimizer::HandleInvalidStep
// Trích từ internal/ceres/trust_region_minimizer.cc, dòng 464–497 (chỉ để xem, không compile)

bool TrustRegionMinimizer::HandleInvalidStep() {
  // TODO(sameeragarwal): Should we be returning FAILURE or
  // NO_CONVERGENCE? The solution value is still usable in many cases,
  // it is not clear if we should declare the solver a failure
  // entirely. For example the case where model_cost_change ~ 0.0, but
  // just slightly negative.
  if (++num_consecutive_invalid_steps_ >=
      options_.max_num_consecutive_invalid_steps) {
    solver_summary_->message = StringPrintf(
        "Number of consecutive invalid steps more "
        "than Solver::Options::max_num_consecutive_invalid_steps: %d",
        options_.max_num_consecutive_invalid_steps);
    solver_summary_->termination_type = FAILURE;
    return false;
  }

  strategy_->StepIsInvalid();

  // We are going to try and reduce the trust region radius and
  // solve again. To do this, we are going to treat this iteration
  // as an unsuccessful iteration. Since the various callbacks are
  // still executed, we are going to fill the iteration summary
  // with data that assumes a step of length zero and no progress.
  iteration_summary_.cost = x_cost_ + solver_summary_->fixed_cost;
  iteration_summary_.cost_change = 0.0;
  iteration_summary_.gradient_max_norm =
      solver_summary_->iterations.back().gradient_max_norm;
  iteration_summary_.gradient_norm =
      solver_summary_->iterations.back().gradient_norm;
  iteration_summary_.step_norm = 0.0;
  iteration_summary_.relative_decrease = 0.0;
  iteration_summary_.eta = options_.eta;
  return true;
}
