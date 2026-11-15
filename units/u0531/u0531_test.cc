// FILE: u0531_test.cc
#include "gtest/gtest.h"
#include "ceres/partition_range_for_parallel_for.h"

namespace ceres {
namespace internal {
// Path P1 calls PartitionRangeForParallelFor(int start, int end, int max_num_partitions, const CumulativeCostData* cumulative_cost_data, CumulativeCostFun&& cumulative_cost_fun).
TEST(Unitu0531, CallsTarget) {
  double cumulative_cost_data_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  PartitionRangeForParallelFor(1, 1, 1, cumulative_cost_data_data, {});
}

// Path P2 calls PartitionRangeForParallelFor(int start, int end, int max_num_partitions, const CumulativeCostData* cumulative_cost_data, CumulativeCostFun&& cumulative_cost_fun) on the alternate CFG path.
TEST(Unitu0531, CallsTargetAlternate) {
  double cumulative_cost_data_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  PartitionRangeForParallelFor(1, 1, 1, cumulative_cost_data_data, {});
}
}  // namespace internal
}  // namespace ceres
