# Unit u0403
## A. Test paths

| Path | ???ng ?i (theo s? node) | C?c nh?nh ?i qua |
|---|---|---|
| P1 | START ? 1 ? END | Kh?ng c? ?i?m r? nh?nh trong CFG. |

## B. B? test case

| Test | Path | Kho?ng gi? tr? ??u v?o | Gi? tr? ?? ch?n |
|---|---|---|---|
| TC1 | P1 | Theo ch? k? `void set_index(int index)` | Gi? tr? h?p l? trong file test |

## C. Nh?nh kh?ng test

Kh?ng c? nh?nh ?i?u khi?n. C2 d? ki?n = 0 / 0.

## D. File test

```cpp
// FILE: u0403_test.cc
#include "gtest/gtest.h"
#include "ceres/residual_block.h"
#include "ceres/cost_function.h"
#include <vector>
class TestCost_u0403 : public ceres::SizedCostFunction<1,1> { public: bool Evaluate(double const* const*, double*, double**) const override { return true; } };
// Path P1: START -> 1 -> END.
TEST(Unit_u0403, PathP1) { TestCost_u0403 cost; ceres::internal::ResidualBlock target(&cost, nullptr, {}, 0); target.set_index(1); }
```
