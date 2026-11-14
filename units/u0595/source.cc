// u0595 – ceres::internal::ConcurrentQueue::PopUnlocked
// Trích từ internal/ceres/concurrent_queue.h, dòng 131–140 (chỉ để xem, không compile)

  bool PopUnlocked(T* value) {
    if (queue_.empty()) {
      return false;
    }

    *value = queue_.front();
    queue_.pop();

    return true;
  }
