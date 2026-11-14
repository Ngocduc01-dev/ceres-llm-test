// u1031 – ceres::internal::ConcurrentQueue::Pop
// Trích từ internal/ceres/concurrent_queue.h, dòng 92–97 (chỉ để xem, không compile)

  bool Pop(T* value) {
    CHECK(value != nullptr);

    std::lock_guard<std::mutex> lock(mutex_);
    return PopUnlocked(value);
  }
