// u0970 – ceres::internal::ThreadPool::ThreadMainLoop
// Trích từ internal/ceres/thread_pool.cc, dòng 95–100 (chỉ để xem, không compile)

void ThreadPool::ThreadMainLoop() {
  std::function<void()> task;
  while (task_queue_.Wait(&task)) {
    task();
  }
}
