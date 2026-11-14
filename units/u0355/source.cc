// u0355 – ceres::internal::BlockUntilFinished::Block
// Trích từ internal/ceres/parallel_invoke.cc, dòng 59–63 (chỉ để xem, không compile)

void BlockUntilFinished::Block() {
  std::unique_lock<std::mutex> lock(mutex_);
  condition_.wait(
      lock, [this]() { return num_total_jobs_finished_ == num_total_jobs_; });
}
