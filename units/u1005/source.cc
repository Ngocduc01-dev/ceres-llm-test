// u1005 – ceres::internal::LineSearchFunction::ResetTimeStatistics
// Trích từ internal/ceres/line_search.cc, dòng 149–161 (chỉ để xem, không compile)

void LineSearchFunction::ResetTimeStatistics() {
  const std::map<std::string, CallStatistics> evaluator_statistics =
      evaluator_->Statistics();

  initial_evaluator_residual_time_in_seconds =
      FindWithDefault(
          evaluator_statistics, "Evaluator::Residual", CallStatistics())
          .time;
  initial_evaluator_jacobian_time_in_seconds =
      FindWithDefault(
          evaluator_statistics, "Evaluator::Jacobian", CallStatistics())
          .time;
}
