// u1394 – ceres::internal::TrustRegionMinimizer::FinalizeIterationAndCheckIfMinimizerCanContinue
// Trích từ internal/ceres/trust_region_minimizer.cc, dòng 314–358 (chỉ để xem, không compile)

bool TrustRegionMinimizer::FinalizeIterationAndCheckIfMinimizerCanContinue() {
  if (iteration_summary_.step_is_successful) {
    ++solver_summary_->num_successful_steps;
    if (x_cost_ < minimum_cost_) {
      minimum_cost_ = x_cost_;
      VectorRef(parameters_, num_parameters_) = x_;
      iteration_summary_.step_is_nonmonotonic = false;
    } else {
      iteration_summary_.step_is_nonmonotonic = true;
    }
  } else {
    ++solver_summary_->num_unsuccessful_steps;
  }

  iteration_summary_.trust_region_radius = strategy_->Radius();
  iteration_summary_.iteration_time_in_seconds =
      WallTimeInSeconds() - iteration_start_time_in_secs_;
  iteration_summary_.cumulative_time_in_seconds =
      WallTimeInSeconds() - start_time_in_secs_ +
      solver_summary_->preprocessor_time_in_seconds;

  solver_summary_->iterations.push_back(iteration_summary_);

  if (!RunCallbacks(options_, iteration_summary_, solver_summary_)) {
    return false;
  }

  if (MaxSolverTimeReached()) {
    return false;
  }

  if (MaxSolverIterationsReached()) {
    return false;
  }

  if (GradientToleranceReached()) {
    return false;
  }

  if (MinTrustRegionRadiusReached()) {
    return false;
  }

  return true;
}
