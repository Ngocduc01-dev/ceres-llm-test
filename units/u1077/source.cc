// u1077 – ceres::internal::ScopedExecutionTimer::ScopedExecutionTimer
// Trích từ internal/ceres/execution_summary.h, dòng 72–75 (chỉ để xem, không compile)

  ScopedExecutionTimer(std::string name, ExecutionSummary* summary)
      : start_time_(WallTimeInSeconds()),
        name_(std::move(name)),
        summary_(summary) {}
