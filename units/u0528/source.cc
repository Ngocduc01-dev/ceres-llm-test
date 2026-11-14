// u0528 – ceres::internal::InvokeOnSegment
// Trích từ internal/ceres/parallel_invoke.h, dòng 58–71 (chỉ để xem, không compile)

template <typename F>
void InvokeOnSegment(int thread_id, std::tuple<int, int> range, F&& function) {
  constexpr bool kExplicitLoop =
      std::is_invocable_v<F, int> || std::is_invocable_v<F, int, int>;

  if constexpr (kExplicitLoop) {
    const auto [start, end] = range;
    for (int i = start; i != end; ++i) {
      InvokeWithThreadId(thread_id, std::forward<F>(function), i);
    }
  } else {
    InvokeWithThreadId(thread_id, std::forward<F>(function), range);
  }
}
