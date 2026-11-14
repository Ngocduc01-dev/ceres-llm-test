// u0945 – ceres::internal::ParallelFor
// Trích từ internal/ceres/parallel_for.h, dòng 69–93 (chỉ để xem, không compile)

template <typename F>
void ParallelFor(ContextImpl* context,
                 int start,
                 int end,
                 int num_threads,
                 F&& function,
                 int min_block_size = 1) {
  CHECK_GT(num_threads, 0);
  if (start >= end) {
    return;
  }

  if (num_threads == 1 || end - start < min_block_size * 2) {
    InvokeOnSegment(0, std::make_tuple(start, end), std::forward<F>(function));
    return;
  }

  CHECK(context != nullptr);
  ParallelInvoke(context,
                 start,
                 end,
                 num_threads,
                 std::forward<F>(function),
                 min_block_size);
}
