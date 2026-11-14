// u0512 – ceres::internal::IsSolutionUsable
// Trích từ internal/ceres/solver_utils.h, dòng 44–49 (chỉ để xem, không compile)

template <typename SummaryType>
bool IsSolutionUsable(const SummaryType& summary) {
  return (summary.termination_type == CONVERGENCE ||
          summary.termination_type == NO_CONVERGENCE ||
          summary.termination_type == USER_SUCCESS);
}
