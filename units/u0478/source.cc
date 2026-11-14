// u0478 – ceres::internal::InvokeWithThreadId
// Trích từ internal/ceres/parallel_invoke.h, dòng 45–54 (chỉ để xem, không compile)

template <typename F, typename... Args>
void InvokeWithThreadId(int thread_id, F&& function, Args&&... args) {
  constexpr bool kPassThreadId = std::is_invocable_v<F, int, Args...>;

  if constexpr (kPassThreadId) {
    function(thread_id, std::forward<Args>(args)...);
  } else {
    function(std::forward<Args>(args)...);
  }
}
