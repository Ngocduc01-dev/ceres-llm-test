// u1421 – ceres::internal::ContextImpl::EnsureMinimumThreads
// Trích từ internal/ceres/context_impl.cc, dòng 192–194 (chỉ để xem, không compile)

void ContextImpl::EnsureMinimumThreads(int num_threads) {
  thread_pool.Resize(num_threads);
}
