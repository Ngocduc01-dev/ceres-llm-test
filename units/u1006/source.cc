// u1006 – ceres::internal::LineSearchFunction::TimeStatistics
// Trích từ internal/ceres/line_search.cc, dòng 163–184 (chỉ để xem, không compile)

void LineSearchFunction::TimeStatistics(
    double* cost_evaluation_time_in_seconds,
    double* gradient_evaluation_time_in_seconds) const {
  const std::map<std::string, CallStatistics> evaluator_time_statistics =
      evaluator_->Statistics();
  *cost_evaluation_time_in_seconds =
      FindWithDefault(
          evaluator_time_statistics, "Evaluator::Residual", CallStatistics())
          .time -
      initial_evaluator_residual_time_in_seconds;
  // Strictly speaking this will slightly underestimate the time spent
  // evaluating the gradient of the line search univariate cost function as it
  // does not count the time spent performing the dot product with the direction
  // vector.  However, this will typically be small by comparison, and also
  // allows direct subtraction of the timing information from the totals for
  // the evaluator returned in the solver summary.
  *gradient_evaluation_time_in_seconds =
      FindWithDefault(
          evaluator_time_statistics, "Evaluator::Jacobian", CallStatistics())
          .time -
      initial_evaluator_jacobian_time_in_seconds;
}
