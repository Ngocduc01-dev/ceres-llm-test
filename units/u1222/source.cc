// u1222 – ceres::internal::(anonymous)::GetNumAllowedThreads
// Trích từ internal/ceres/thread_pool.cc, dòng 42–44 (chỉ để xem, không compile)

int GetNumAllowedThreads(int requested_num_threads) {
  return std::min(requested_num_threads, ThreadPool::MaxNumThreadsAvailable());
}
