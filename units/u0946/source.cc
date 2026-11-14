// u0946 – ceres::internal::ParallelFor
// Trích từ internal/ceres/parallel_for.h, dòng 154–183 (chỉ để xem, không compile)

template <typename F, typename CumulativeCostData, typename CumulativeCostFun>
void ParallelFor(ContextImpl* context,
                 int start,
                 int end,
                 int num_threads,
                 F&& function,
                 const CumulativeCostData* cumulative_cost_data,
                 CumulativeCostFun&& cumulative_cost_fun) {
  CHECK_GT(num_threads, 0);
  if (start >= end) {
    return;
  }
  if (num_threads == 1 || end - start <= num_threads) {
    ParallelFor(context, start, end, num_threads, std::forward<F>(function));
    return;
  }
  // Creating several partitions allows us to tolerate imperfections of
  // partitioning and user-supplied iteration costs up to a certain extent
  constexpr int kNumPartitionsPerThread = 4;
  const int kMaxPartitions = num_threads * kNumPartitionsPerThread;
  const auto& partitions = PartitionRangeForParallelFor(
      start,
      end,
      kMaxPartitions,
      cumulative_cost_data,
      std::forward<CumulativeCostFun>(cumulative_cost_fun));
  CHECK_GT(partitions.size(), 1);
  ParallelFor(
      context, start, end, num_threads, std::forward<F>(function), partitions);
}
