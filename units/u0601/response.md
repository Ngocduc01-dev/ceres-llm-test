**A. Test paths**

| Path | ???ng ?i (theo s? node) | C?c nh?nh ?i qua |
|---|---|---|
| P1 | START ? 1 ? END | CFG branch path 1 |

**B. B? test case**

| Test | Path | Kho?ng gi? tr? ??u v?o | Gi? tr? ?? ch?n |
|---|---|---|---|
| TC1 | P1 | valid values from prompt signature | deterministic small value |

**C. Nh?nh kh?ng test**

Kh?ng k?ch ho?t nh?nh CHECK l?m d?ng ch??ng tr?nh. C2 d? ki?n = 2 / 2

**D. File test**

```cpp
// FILE: u0601_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"

// Path P1 calls DeleteBlockInVector(std::vector<Block*>* mutable_blocks, Block* block_to_remove).
TEST(Unitu0601, CallsTarget) {
  double mutable_blocks_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double block_to_remove_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.DeleteBlockInVector(mutable_blocks_data, block_to_remove_data);
}
```
