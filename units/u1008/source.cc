// u1008 – ceres::internal::TypedLinearSolver::Statistics
// Trích từ internal/ceres/linear_solver.h, dòng 378–380 (chỉ để xem, không compile)

  std::map<std::string, CallStatistics> Statistics() const override {
    return execution_summary_.statistics();
  }
