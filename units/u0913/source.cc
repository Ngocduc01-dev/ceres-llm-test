// u0913 – ceres::internal::ThreadPool::MaxNumThreadsAvailable
// Trích từ internal/ceres/thread_pool.cc, dòng 48–54 (chỉ để xem, không compile)

int ThreadPool::MaxNumThreadsAvailable() {
  const int num_hardware_threads = std::thread::hardware_concurrency();
  // hardware_concurrency() can return 0 if the value is not well defined or not
  // computable.
  return num_hardware_threads == 0 ? std::numeric_limits<int>::max()
                                   : num_hardware_threads;
}
