// u0669 – ceres::internal::ExecutionSummary::IncrementTimeBy
// Trích từ internal/ceres/execution_summary.h, dòng 54–59 (chỉ để xem, không compile)

  void IncrementTimeBy(const std::string& name, const double value) {
    std::lock_guard<std::mutex> l(mutex_);
    CallStatistics& call_stats = statistics_[name];
    call_stats.time += value;
    ++call_stats.calls;
  }
