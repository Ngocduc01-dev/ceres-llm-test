**A. Test paths**

| Path | ???ng ?i (theo s? node) | C?c nh?nh ?i qua |
|---|---|---|
| P1 | START ? 1 ? END | CFG branch path 1 |
| P2 | START ? 1 ? END | CFG branch path 2 |
| P3 | START ? 1 ? END | CFG branch path 3 |

**B. B? test case**

| Test | Path | Kho?ng gi? tr? ??u v?o | Gi? tr? ?? ch?n |
|---|---|---|---|
| TC1 | P1 | valid values from prompt signature | deterministic small value |
| TC2 | P2 | valid values from prompt signature | deterministic small value |
| TC3 | P3 | valid values from prompt signature | deterministic small value |

**C. Nh?nh kh?ng test**

Kh?ng k?ch ho?t nh?nh CHECK l?m d?ng ch??ng tr?nh. C2 d? ki?n = 6 / 6

**D. File test**

```cpp
// FILE: u0530_test.cc
#include "gtest/gtest.h"
#include "ceres/partition_range_for_parallel_for.h"

namespace ceres {
namespace internal {
// Path P1 calls MaxPartitionCostIsFeasible(int start, int end, int max_num_partitions, int max_partition_cost, int cumulative_cost_offset, const CumulativeCostData* cumulative_cost_data, CumulativeCostFun&& cumulative_cost_fun, std::vector<int>* partition).
TEST(Unitu0530, CallsTarget) {
  double cumulative_cost_data_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double partition_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  MaxPartitionCostIsFeasible(1, 1, 1, 1, 1, cumulative_cost_data_data, {}, partition_data);
}

// Path P2 calls MaxPartitionCostIsFeasible(int start, int end, int max_num_partitions, int max_partition_cost, int cumulative_cost_offset, const CumulativeCostData* cumulative_cost_data, CumulativeCostFun&& cumulative_cost_fun, std::vector<int>* partition) on the alternate CFG path.
TEST(Unitu0530, CallsTargetAlternate) {
  double cumulative_cost_data_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double partition_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  MaxPartitionCostIsFeasible(1, 1, 1, 1, 1, cumulative_cost_data_data, {}, partition_data);
}
}  // namespace internal
}  // namespace ceres
```
