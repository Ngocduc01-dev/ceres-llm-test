// u0899 – ceres::internal::ThreadPool::Size
// Trích từ internal/ceres/thread_pool.cc, dòng 90–93 (chỉ để xem, không compile)

int ThreadPool::Size() {
  std::lock_guard<std::mutex> lock(thread_pool_mutex_);
  return thread_pool_.size();
}
