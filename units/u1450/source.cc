// u1450 – ceres::internal::TrustRegionMinimizer::DoLineSearch
// Trích từ internal/ceres/trust_region_minimizer.cc, dòng 587–632 (chỉ để xem, không compile)

void TrustRegionMinimizer::DoLineSearch(const Vector& x,
                                        const Vector& gradient,
                                        const double cost,
                                        Vector* delta) {
  LineSearchFunction line_search_function(evaluator_);

  LineSearch::Options line_search_options;
  line_search_options.is_silent = true;
  line_search_options.interpolation_type =
      options_.line_search_interpolation_type;
  line_search_options.min_step_size = options_.min_line_search_step_size;
  line_search_options.sufficient_decrease =
      options_.line_search_sufficient_function_decrease;
  line_search_options.max_step_contraction =
      options_.max_line_search_step_contraction;
  line_search_options.min_step_contraction =
      options_.min_line_search_step_contraction;
  line_search_options.max_num_iterations =
      options_.max_num_line_search_step_size_iterations;
  line_search_options.sufficient_curvature_decrease =
      options_.line_search_sufficient_curvature_decrease;
  line_search_options.max_step_expansion =
      options_.max_line_search_step_expansion;
  line_search_options.function = &line_search_function;

  std::string message;
  std::unique_ptr<LineSearch> line_search(
      LineSearch::Create(ceres::ARMIJO, line_search_options, &message));
  LineSearch::Summary line_search_summary;
  line_search_function.Init(x, *delta);
  line_search->Search(1.0, cost, gradient.dot(*delta), &line_search_summary);

  solver_summary_->num_line_search_steps += line_search_summary.num_iterations;
  solver_summary_->line_search_cost_evaluation_time_in_seconds +=
      line_search_summary.cost_evaluation_time_in_seconds;
  solver_summary_->line_search_gradient_evaluation_time_in_seconds +=
      line_search_summary.gradient_evaluation_time_in_seconds;
  solver_summary_->line_search_polynomial_minimization_time_in_seconds +=
      line_search_summary.polynomial_minimization_time_in_seconds;
  solver_summary_->line_search_total_time_in_seconds +=
      line_search_summary.total_time_in_seconds;

  if (line_search_summary.success) {
    *delta *= line_search_summary.optimal_point.x;
  }
}
