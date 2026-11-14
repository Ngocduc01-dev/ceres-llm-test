// u1048 – ceres::internal::ConcurrentQueue::Wait
// Trích từ internal/ceres/concurrent_queue.h, dòng 102–110 (chỉ để xem, không compile)

  bool Wait(T* value) {
    CHECK(value != nullptr);

    std::unique_lock<std::mutex> lock(mutex_);
    work_pending_condition_.wait(lock,
                                 [&]() { return !(wait_ && queue_.empty()); });

    return PopUnlocked(value);
  }
