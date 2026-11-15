// FILE: u0531_test.cc
#include "gtest/gtest.h"
#include "ceres/partition_range_for_parallel_for.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0531, CallsTarget) {
  double cumulative_cost_data_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  PartitionRangeForParallelFor(1, 1, 1, cumulative_cost_data_data, {});
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0531, CallsTargetAlternate) {
  double cumulative_cost_data_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  PartitionRangeForParallelFor(1, 1, 1, cumulative_cost_data_data, {});
}
}  // namespace internal
}  // namespace ceres
