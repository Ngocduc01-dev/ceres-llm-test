// u0269 – ceres::internal::ConcurrentQueue::Push
// Trích từ internal/ceres/concurrent_queue.h, dòng 84–88 (chỉ để xem, không compile)

  void Push(const T& value) {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push(value);
    work_pending_condition_.notify_one();
  }
