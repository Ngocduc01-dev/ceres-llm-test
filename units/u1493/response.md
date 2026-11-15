# A. Test paths

| Path | ???ng ?i (theo s? node) | C?c nh?nh ?i qua |
|---|---|---|
| P1 | START ? 1 ? END | node 1: ???ng ?i kh? thi P1 |

# B. B? test case

| Test | Path | Kho?ng gi? tr? ??u v?o | Gi? tr? ?? ch?n |
|---|---|---|---|
| TC1 | P1 | D? li?u h?p l? theo prompt | Gi? tr? c? ??nh an to?n |

# C. Nh?nh kh?ng test

Kh?ng c? nh?nh b? b? qua ngo?i c?c nh?nh CHECK kh?ng th? l?m sai theo y?u c?u harness.

C2 d? ki?n = 0 / 0

# D. File test

```cpp
// FILE: u1493_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/coordinate_descent_minimizer.h"
#include "ceres/evaluator.h"
#include "ceres/linear_solver.h"
#include "ceres/minimizer.h"
#include "ceres/program.h"
#include "ceres/trust_region_minimizer.h"
#include "ceres/trust_region_strategy.h"

// P1: START -> 1 -> END
TEST(u1493_Test, TC1_CallsTarget) {
  ceres::internal::CoordinateDescentMinimizer target{};
  target.Solve(nullptr, nullptr, nullptr, nullptr);
}
```
