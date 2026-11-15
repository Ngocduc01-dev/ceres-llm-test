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
// FILE: u1324_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_cholesky.h"
#include "ceres/dense_normal_cholesky_solver.h"
#include "ceres/linear_solver.h"

// P1: START -> 1 -> END
TEST(u1324_Test, TC1_CallsTarget) {
  ceres::internal::DenseNormalCholeskySolver target{};
}
```
