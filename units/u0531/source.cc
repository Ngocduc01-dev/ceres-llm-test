// u0531 – ceres::internal::PartitionRangeForParallelFor
// Trích từ internal/ceres/partition_range_for_parallel_for.h, dòng 94–147 (chỉ để xem, không compile)

template <typename CumulativeCostData, typename CumulativeCostFun>
std::vector<int> PartitionRangeForParallelFor(
    int start,
    int end,
    int max_num_partitions,
    const CumulativeCostData* cumulative_cost_data,
    CumulativeCostFun&& cumulative_cost_fun) {
  // Given maximal partition cost, it is possible to verify if it is admissible
  // and obtain corresponding partition using MaxPartitionCostIsFeasible
  // function. In order to find the lowest admissible value, a binary search
  // over all potentially optimal cost values is being performed
  const int cumulative_cost_last =
      cumulative_cost_fun(cumulative_cost_data[end - 1]);
  const int cumulative_cost_offset =
      start ? cumulative_cost_fun(cumulative_cost_data[start - 1]) : 0;
  const int total_cost = cumulative_cost_last - cumulative_cost_offset;

  // Minimal maximal partition cost is not smaller than the average
  // We will use non-inclusive lower bound
  int partition_cost_lower_bound = total_cost / max_num_partitions - 1;
  // Minimal maximal partition cost is not larger than the total cost
  // Upper bound is inclusive
  int partition_cost_upper_bound = total_cost;

  std::vector<int> partition;
  // Range partition corresponding to the latest evaluated upper bound.
  // A single segment covering the whole input interval [start, end) corresponds
  // to minimal maximal partition cost of total_cost.
  std::vector<int> partition_upper_bound = {start, end};
  // Binary search over partition cost, returning the lowest admissible cost
  while (partition_cost_upper_bound - partition_cost_lower_bound > 1) {
    partition.reserve(max_num_partitions + 1);
    const int partition_cost =
        partition_cost_lower_bound +
        (partition_cost_upper_bound - partition_cost_lower_bound) / 2;
    bool admissible = MaxPartitionCostIsFeasible(
        start,
        end,
        max_num_partitions,
        partition_cost,
        cumulative_cost_offset,
        cumulative_cost_data,
        std::forward<CumulativeCostFun>(cumulative_cost_fun),
        &partition);
    if (admissible) {
      partition_cost_upper_bound = partition_cost;
      std::swap(partition, partition_upper_bound);
    } else {
      partition_cost_lower_bound = partition_cost;
    }
  }

  return partition_upper_bound;
}
