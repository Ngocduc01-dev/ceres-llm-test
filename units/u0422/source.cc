// u0422 – ceres::internal::ThreadTokenProvider::Release
// Trích từ internal/ceres/thread_token_provider.cc, dòng 47–47 (chỉ để xem, không compile)

void ThreadTokenProvider::Release(int thread_id) { pool_.Push(thread_id); }
