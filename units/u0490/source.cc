// u0490 – ceres::internal::ThreadTokenProvider::ThreadTokenProvider
// Trích từ internal/ceres/thread_token_provider.cc, dòng 35–39 (chỉ để xem, không compile)

ThreadTokenProvider::ThreadTokenProvider(int num_threads) {
  for (int i = 0; i < num_threads; i++) {
    pool_.Push(i);
  }
}
