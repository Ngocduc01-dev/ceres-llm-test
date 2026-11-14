// u0491 – ceres::internal::ThreadTokenProvider::Acquire
// Trích từ internal/ceres/thread_token_provider.cc, dòng 41–45 (chỉ để xem, không compile)

int ThreadTokenProvider::Acquire() {
  int thread_id;
  CHECK(pool_.Wait(&thread_id));
  return thread_id;
}
