// u1360 – ceres::internal::ThreadPool::Resize
// Trích từ internal/ceres/thread_pool.cc, dòng 70–84 (chỉ để xem, không compile)

void ThreadPool::Resize(int num_threads) {
  std::lock_guard<std::mutex> lock(thread_pool_mutex_);

  const int num_current_threads = thread_pool_.size();
  if (num_current_threads >= num_threads) {
    return;
  }

  const int create_num_threads =
      GetNumAllowedThreads(num_threads) - num_current_threads;

  for (int i = 0; i < create_num_threads; ++i) {
    thread_pool_.emplace_back(&ThreadPool::ThreadMainLoop, this);
  }
}
