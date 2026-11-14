// u1350 – ceres::internal::LineSearch::Search
// Trích từ internal/ceres/line_search.cc, dòng 186–204 (chỉ để xem, không compile)

void LineSearch::Search(double step_size_estimate,
                        double initial_cost,
                        double initial_gradient,
                        Summary* summary) const {
  const double start_time = WallTimeInSeconds();
  CHECK(summary != nullptr);
  *summary = LineSearch::Summary();

  summary->cost_evaluation_time_in_seconds = 0.0;
  summary->gradient_evaluation_time_in_seconds = 0.0;
  summary->polynomial_minimization_time_in_seconds = 0.0;
  options().function->ResetTimeStatistics();
  this->DoSearch(step_size_estimate, initial_cost, initial_gradient, summary);
  options().function->TimeStatistics(
      &summary->cost_evaluation_time_in_seconds,
      &summary->gradient_evaluation_time_in_seconds);

  summary->total_time_in_seconds = WallTimeInSeconds() - start_time;
}
