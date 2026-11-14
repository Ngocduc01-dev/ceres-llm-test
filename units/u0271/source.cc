// u0271 – ceres::internal::ConcurrentQueue::EnableWaiters
// Trích từ internal/ceres/concurrent_queue.h, dòng 122–125 (chỉ để xem, không compile)

  void EnableWaiters() {
    std::lock_guard<std::mutex> lock(mutex_);
    wait_ = true;
  }
