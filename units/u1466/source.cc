// u1466 – ceres::internal::TrustRegionMinimizer::DoInnerIterationsIfNeeded
// Trích từ internal/ceres/trust_region_minimizer.cc, dòng 506–578 (chỉ để xem, không compile)

void TrustRegionMinimizer::DoInnerIterationsIfNeeded() {
  inner_iterations_were_useful_ = false;
  if (!inner_iterations_are_enabled_ ||
      candidate_cost_ >= std::numeric_limits<double>::max()) {
    return;
  }

  double inner_iteration_start_time = WallTimeInSeconds();
  ++solver_summary_->num_inner_iteration_steps;
  inner_iteration_x_ = candidate_x_;
  Solver::Summary inner_iteration_summary;
  options_.inner_iteration_minimizer->Minimize(
      options_, inner_iteration_x_.data(), &inner_iteration_summary);
  double inner_iteration_cost;
  if (!evaluator_->Evaluate(inner_iteration_x_.data(),
                            &inner_iteration_cost,
                            nullptr,
                            nullptr,
                            nullptr)) {
    if (is_not_silent_) {
      VLOG(2) << "Inner iteration failed.";
    }
    return;
  }

  if (is_not_silent_) {
    VLOG(2) << "Inner iteration succeeded; Current cost: " << x_cost_
            << " Trust region step cost: " << candidate_cost_
            << " Inner iteration cost: " << inner_iteration_cost;
  }
  candidate_x_ = inner_iteration_x_;

  // Normally, the quality of a trust region step is measured by
  // the ratio
  //
  //              cost_change
  //    r =    -----------------
  //           model_cost_change
  //
  // All the change in the nonlinear objective is due to the trust
  // region step so this ratio is a good measure of the quality of
  // the trust region radius. However, when inner iterations are
  // being used, cost_change includes the contribution of the
  // inner iterations and its not fair to credit it all to the
  // trust region algorithm. So we change the ratio to be
  //
  //                              cost_change
  //    r =    ------------------------------------------------
  //           (model_cost_change + inner_iteration_cost_change)
  //
  // Practically we do this by increasing model_cost_change by
  // inner_iteration_cost_change.

  const double inner_iteration_cost_change =
      candidate_cost_ - inner_iteration_cost;
  model_cost_change_ += inner_iteration_cost_change;
  inner_iterations_were_useful_ = inner_iteration_cost < x_cost_;
  const double inner_iteration_relative_progress =
      1.0 - inner_iteration_cost / candidate_cost_;

  // Disable inner iterations once the relative improvement
  // drops below tolerance.
  inner_iterations_are_enabled_ =
      (inner_iteration_relative_progress > options_.inner_iteration_tolerance);
  if (is_not_silent_ && !inner_iterations_are_enabled_) {
    VLOG(2) << "Disabling inner iterations. Progress : "
            << inner_iteration_relative_progress;
  }
  candidate_cost_ = inner_iteration_cost;

  solver_summary_->inner_iteration_time_in_seconds +=
      WallTimeInSeconds() - inner_iteration_start_time;
}
