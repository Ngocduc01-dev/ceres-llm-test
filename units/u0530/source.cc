// u0530 – ceres::internal::MaxPartitionCostIsFeasible
// Trích từ internal/ceres/partition_range_for_parallel_for.h, dòng 47–87 (chỉ để xem, không compile)

template <typename CumulativeCostData, typename CumulativeCostFun>
bool MaxPartitionCostIsFeasible(int start,
                                int end,
                                int max_num_partitions,
                                int max_partition_cost,
                                int cumulative_cost_offset,
                                const CumulativeCostData* cumulative_cost_data,
                                CumulativeCostFun&& cumulative_cost_fun,
                                std::vector<int>* partition) {
  partition->clear();
  partition->push_back(start);
  int partition_start = start;
  int cost_offset = cumulative_cost_offset;

  while (partition_start < end) {
    // Already have max_num_partitions
    if (partition->size() > max_num_partitions) {
      return false;
    }
    const int target = max_partition_cost + cost_offset;
    const int partition_end =
        std::partition_point(
            cumulative_cost_data + partition_start,
            cumulative_cost_data + end,
            [&cumulative_cost_fun, target](const CumulativeCostData& item) {
              return cumulative_cost_fun(item) <= target;
            }) -
        cumulative_cost_data;
    // Unable to make a partition from a single element
    if (partition_end == partition_start) {
      return false;
    }

    const int cost_last =
        cumulative_cost_fun(cumulative_cost_data[partition_end - 1]);
    partition->push_back(partition_end);
    partition_start = partition_end;
    cost_offset = cost_last;
  }
  return true;
}
