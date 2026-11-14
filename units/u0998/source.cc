// u0998 – ceres::internal::ScopedExecutionTimer::~ScopedExecutionTimer
// Trích từ internal/ceres/execution_summary.h, dòng 77–79 (chỉ để xem, không compile)

  ~ScopedExecutionTimer() {
    summary_->IncrementTimeBy(name_, WallTimeInSeconds() - start_time_);
  }
