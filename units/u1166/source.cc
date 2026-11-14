// u1166 – ceres::internal::ThreadPool::~ThreadPool
// Trích từ internal/ceres/thread_pool.cc, dòng 60–68 (chỉ để xem, không compile)

ThreadPool::~ThreadPool() {
  std::lock_guard<std::mutex> lock(thread_pool_mutex_);
  // Signal the thread workers to stop and wait for them to finish all scheduled
  // tasks.
  Stop();
  for (std::thread& thread : thread_pool_) {
    thread.join();
  }
}
