// u1002 – ceres::internal::GradientProblemEvaluator::Statistics
// Trích từ internal/ceres/gradient_problem_evaluator.h, dòng 90–92 (chỉ để xem, không compile)

  std::map<std::string, internal::CallStatistics> Statistics() const final {
    return execution_summary_.statistics();
  }
