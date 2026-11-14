// u0952 – ceres::internal::ParallelFor
// Trích từ internal/ceres/parallel_for.h, dòng 100–136 (chỉ để xem, không compile)

template <typename F>
void ParallelFor(ContextImpl* context,
                 int start,
                 int end,
                 int num_threads,
                 F&& function,
                 const std::vector<int>& partitions) {
  CHECK_GT(num_threads, 0);
  if (start >= end) {
    return;
  }
  CHECK_EQ(partitions.front(), start);
  CHECK_EQ(partitions.back(), end);
  if (num_threads == 1 || end - start <= num_threads) {
    ParallelFor(context, start, end, num_threads, std::forward<F>(function));
    return;
  }
  CHECK_GT(partitions.size(), 1);
  const int num_partitions = partitions.size() - 1;
  ParallelFor(context,
              0,
              num_partitions,
              num_threads,
              [&function, &partitions](int thread_id,
                                       std::tuple<int, int> partition_ids) {
                // partition_ids is a range of partition indices
                const auto [partition_start, partition_end] = partition_ids;
                // Execution over several adjacent segments is equivalent
                // to execution over union of those segments (which is also a
                // contiguous segment)
                const int range_start = partitions[partition_start];
                const int range_end = partitions[partition_end];
                // Range of original loop indices
                const auto range = std::make_tuple(range_start, range_end);
                InvokeOnSegment(thread_id, range, function);
              });
}
