// u0270 – ceres::internal::ConcurrentQueue::StopWaiters
// Trích từ internal/ceres/concurrent_queue.h, dòng 115–119 (chỉ để xem, không compile)

  void StopWaiters() {
    std::lock_guard<std::mutex> lock(mutex_);
    wait_ = false;
    work_pending_condition_.notify_all();
  }
