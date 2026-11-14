// u1377 – ceres::internal::TrustRegionMinimizer::ComputeTrustRegionStep
// Trích từ internal/ceres/trust_region_minimizer.cc, dòng 378–459 (chỉ để xem, không compile)

bool TrustRegionMinimizer::ComputeTrustRegionStep() {
  const double strategy_start_time = WallTimeInSeconds();
  iteration_summary_.step_is_valid = false;
  TrustRegionStrategy::PerSolveOptions per_solve_options;
  per_solve_options.eta = options_.eta;
  if (find(options_.trust_region_minimizer_iterations_to_dump.begin(),
           options_.trust_region_minimizer_iterations_to_dump.end(),
           iteration_summary_.iteration) !=
      options_.trust_region_minimizer_iterations_to_dump.end()) {
    per_solve_options.dump_format_type =
        options_.trust_region_problem_dump_format_type;
    per_solve_options.dump_filename_base =
        JoinPath(options_.trust_region_problem_dump_directory,
                 StringPrintf("ceres_solver_iteration_%03d",
                              iteration_summary_.iteration));
  }

  TrustRegionStrategy::Summary strategy_summary =
      strategy_->ComputeStep(per_solve_options,
                             jacobian_,
                             residuals_.data(),
                             trust_region_step_.data());

  if (strategy_summary.termination_type ==
      LinearSolverTerminationType::FATAL_ERROR) {
    solver_summary_->message =
        "Linear solver failed due to unrecoverable "
        "non-numeric causes. Please see the error log for clues. ";
    solver_summary_->termination_type = FAILURE;
    return false;
  }

  iteration_summary_.step_solver_time_in_seconds =
      WallTimeInSeconds() - strategy_start_time;
  iteration_summary_.linear_solver_iterations = strategy_summary.num_iterations;

  if (strategy_summary.termination_type ==
      LinearSolverTerminationType::FAILURE) {
    return true;
  }

  // new_model_cost
  //  = 1/2 [f + J * step]^2
  //  = 1/2 [ f'f + 2f'J * step + step' * J' * J * step ]
  // model_cost_change
  //  = cost - new_model_cost
  //  = f'f/2  - 1/2 [ f'f + 2f'J * step + step' * J' * J * step]
  //  = -f'J * step - step' * J' * J * step / 2
  //  = -(J * step)'(f + J * step / 2)
  ParallelSetZero(options_.context, options_.num_threads, model_residuals_);
  jacobian_->RightMultiplyAndAccumulate(trust_region_step_.data(),
                                        model_residuals_.data(),
                                        options_.context,
                                        options_.num_threads);
  model_cost_change_ = -Dot(model_residuals_,
                            residuals_ + model_residuals_ / 2.0,
                            options_.context,
                            options_.num_threads);

  // TODO(sameeragarwal)
  //
  //  1. What happens if model_cost_change_ = 0
  //  2. What happens if -epsilon <= model_cost_change_ < 0 for some
  //     small epsilon due to round off error.
  iteration_summary_.step_is_valid = (model_cost_change_ > 0.0);
  if (iteration_summary_.step_is_valid) {
    // Undo the Jacobian column scaling.
    ParallelAssign(options_.context,
                   options_.num_threads,
                   delta_,
                   (trust_region_step_.array() * jacobian_scaling_.array()));
    num_consecutive_invalid_steps_ = 0;
  }

  if (is_not_silent_ && !iteration_summary_.step_is_valid) {
    VLOG(1) << "Invalid step: current_cost: " << x_cost_
            << " absolute model cost change: " << model_cost_change_
            << " relative model cost change: "
            << (model_cost_change_ / x_cost_);
  }
  return true;
}
