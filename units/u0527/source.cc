// u0527 – ceres::internal::BlockUntilFinished::Finished
// Trích từ internal/ceres/parallel_invoke.cc, dòng 49–57 (chỉ để xem, không compile)

void BlockUntilFinished::Finished(int num_jobs_finished) {
  if (num_jobs_finished == 0) return;
  std::lock_guard<std::mutex> lock(mutex_);
  num_total_jobs_finished_ += num_jobs_finished;
  CHECK_LE(num_total_jobs_finished_, num_total_jobs_);
  if (num_total_jobs_finished_ == num_total_jobs_) {
    condition_.notify_one();
  }
}
