// u1300 – ceres::internal::LoggingCallback::operator()
// Trích từ internal/ceres/callbacks.cc, dòng 82–126 (chỉ để xem, không compile)

CallbackReturnType LoggingCallback::operator()(
    const IterationSummary& summary) {
  std::string output;
  if (minimizer_type == LINE_SEARCH) {
    output = StringPrintf(
        "% 4d: f:% 8e d:% 3.2e g:% 3.2e h:% 3.2e s:% 3.2e e:% 3d it:% 3.2e "
        "tt:% 3.2e",
        summary.iteration,
        summary.cost,
        summary.cost_change,
        summary.gradient_max_norm,
        summary.step_norm,
        summary.step_size,
        summary.line_search_function_evaluations,
        summary.iteration_time_in_seconds,
        summary.cumulative_time_in_seconds);
  } else if (minimizer_type == TRUST_REGION) {
    // clang-format off
    if (summary.iteration == 0) {
      output = "iter      cost      cost_change  |gradient|   |step|    tr_ratio  tr_radius  ls_iter  iter_time  total_time\n";  // NOLINT
    }
    output += StringPrintf(
        "% 4d % 8e   % 3.2e   % 3.2e  % 3.2e  % 3.2e % 3.2e     % 4d   % 3.2e   % 3.2e",  // NOLINT
        // clang-format on
        summary.iteration,
        summary.cost,
        summary.cost_change,
        summary.gradient_max_norm,
        summary.step_norm,
        summary.relative_decrease,
        summary.trust_region_radius,
        summary.linear_solver_iterations,
        summary.iteration_time_in_seconds,
        summary.cumulative_time_in_seconds);
  } else {
    LOG(FATAL) << "Unknown minimizer type.";
  }

  if (log_to_stdout_) {
    std::cout << output << std::endl;
  } else {
    VLOG(1) << output;
  }
  return SOLVER_CONTINUE;
}
