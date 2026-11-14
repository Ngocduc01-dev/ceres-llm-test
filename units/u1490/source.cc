// u1490 – ceres::internal::TrustRegionMinimizer::Minimize
// Trích từ internal/ceres/trust_region_minimizer.cc, dòng 66–135 (chỉ để xem, không compile)

void TrustRegionMinimizer::Minimize(const Minimizer::Options& options,
                                    double* parameters,
                                    Solver::Summary* solver_summary) {
  start_time_in_secs_ = WallTimeInSeconds();
  iteration_start_time_in_secs_ = start_time_in_secs_;
  Init(options, parameters, solver_summary);
  RETURN_IF_ERROR_AND_LOG(IterationZero());

  // Create the TrustRegionStepEvaluator. The construction needs to be
  // delayed to this point because we need the cost for the starting
  // point to initialize the step evaluator.
  step_evaluator_ = std::make_unique<TrustRegionStepEvaluator>(
      x_cost_,
      options_.use_nonmonotonic_steps
          ? options_.max_consecutive_nonmonotonic_steps
          : 0);

  bool atleast_one_successful_step = false;
  while (FinalizeIterationAndCheckIfMinimizerCanContinue()) {
    iteration_start_time_in_secs_ = WallTimeInSeconds();

    const double previous_gradient_norm = iteration_summary_.gradient_norm;
    const double previous_gradient_max_norm =
        iteration_summary_.gradient_max_norm;

    iteration_summary_ = IterationSummary();
    iteration_summary_.iteration =
        solver_summary->iterations.back().iteration + 1;

    RETURN_IF_ERROR_AND_LOG(ComputeTrustRegionStep());
    if (!iteration_summary_.step_is_valid) {
      RETURN_IF_ERROR_AND_LOG(HandleInvalidStep());
      continue;
    }

    if (options_.is_constrained &&
        options_.max_num_line_search_step_size_iterations > 0) {
      // Use a projected line search to enforce the bounds constraints
      // and improve the quality of the step.
      DoLineSearch(x_, gradient_, x_cost_, &delta_);
    }

    ComputeCandidatePointAndEvaluateCost();
    DoInnerIterationsIfNeeded();

    if (atleast_one_successful_step && ParameterToleranceReached()) {
      return;
    }

    if (FunctionToleranceReached()) {
      return;
    }

    if (IsStepSuccessful()) {
      atleast_one_successful_step = true;
      RETURN_IF_ERROR_AND_LOG(HandleSuccessfulStep());
    } else {
      // Declare the step unsuccessful and inform the trust region strategy.
      iteration_summary_.step_is_successful = false;
      iteration_summary_.cost = candidate_cost_ + solver_summary_->fixed_cost;

      // When the step is unsuccessful, we do not compute the gradient
      // (or update x), so we preserve its value from the last
      // successful iteration.
      iteration_summary_.gradient_norm = previous_gradient_norm;
      iteration_summary_.gradient_max_norm = previous_gradient_max_norm;
      strategy_->StepRejected(iteration_summary_.relative_decrease);
    }
  }
}
