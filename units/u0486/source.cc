// u0486 – ceres::internal::SetSummaryFinalCost
// Trích từ internal/ceres/solver_utils.h, dòng 51–60 (chỉ để xem, không compile)

template <typename SummaryType>
void SetSummaryFinalCost(SummaryType* summary) {
  summary->final_cost = summary->initial_cost;
  // We need the loop here, instead of just looking at the last
  // iteration because the minimizer maybe making non-monotonic steps.
  for (int i = 0; i < summary->iterations.size(); ++i) {
    const IterationSummary& iteration_summary = summary->iterations[i];
    summary->final_cost = std::min(iteration_summary.cost, summary->final_cost);
  }
}
