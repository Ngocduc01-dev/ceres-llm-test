// u1019 – ceres::internal::ProgramEvaluator::Statistics
// Trích từ internal/ceres/program_evaluator.h, dòng 317–319 (chỉ để xem, không compile)

  std::map<std::string, CallStatistics> Statistics() const final {
    return execution_summary_.statistics();
  }
