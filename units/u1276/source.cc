// u1276 – ceres::internal::TrustRegionMinimizer::IterationZero
// Trích từ internal/ceres/trust_region_minimizer.cc, dòng 194–230 (chỉ để xem, không compile)

bool TrustRegionMinimizer::IterationZero() {
  iteration_summary_ = IterationSummary();
  iteration_summary_.iteration = 0;
  iteration_summary_.step_is_valid = false;
  iteration_summary_.step_is_successful = false;
  iteration_summary_.cost_change = 0.0;
  iteration_summary_.gradient_max_norm = 0.0;
  iteration_summary_.gradient_norm = 0.0;
  iteration_summary_.step_norm = 0.0;
  iteration_summary_.relative_decrease = 0.0;
  iteration_summary_.eta = options_.eta;
  iteration_summary_.linear_solver_iterations = 0;
  iteration_summary_.step_solver_time_in_seconds = 0;

  if (options_.is_constrained) {
    delta_.setZero();
    if (!evaluator_->Plus(x_.data(), delta_.data(), candidate_x_.data())) {
      solver_summary_->message =
          "Unable to project initial point onto the feasible set.";
      solver_summary_->termination_type = FAILURE;
      return false;
    }

    x_ = candidate_x_;
  }

  if (!EvaluateGradientAndJacobian(/*new_evaluation_point=*/true)) {
    solver_summary_->message =
        "Initial residual and Jacobian evaluation failed.";
    return false;
  }

  solver_summary_->initial_cost = x_cost_ + solver_summary_->fixed_cost;
  iteration_summary_.step_is_valid = true;
  iteration_summary_.step_is_successful = true;
  return true;
}
