// u0477 – ceres::internal::MakeConditionalLock
// Trích từ internal/ceres/parallel_for.h, dòng 48–52 (chỉ để xem, không compile)

inline decltype(auto) MakeConditionalLock(const int num_threads,
                                          std::mutex& m) {
  return (num_threads == 1) ? std::unique_lock<std::mutex>{}
                            : std::unique_lock<std::mutex>{m};
}
