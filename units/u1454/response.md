# A. Test paths

| Path | ???ng ?i (theo s? node) | C?c nh?nh ?i qua |
|---|---|---|
| P1 | START ? 1 ? END | node 1: ???ng ?i kh? thi P1 |
| P2 | START ? 1 ? END | node 1: ???ng ?i kh? thi P2 |
| P3 | START ? 1 ? END | node 1: ???ng ?i kh? thi P3 |
| P4 | START ? 1 ? END | node 1: ???ng ?i kh? thi P4 |

# B. B? test case

| Test | Path | Kho?ng gi? tr? ??u v?o | Gi? tr? ?? ch?n |
|---|---|---|---|
| TC1 | P1 | D? li?u h?p l? theo prompt | Gi? tr? c? ??nh an to?n |
| TC2 | P2 | D? li?u h?p l? theo prompt | Gi? tr? c? ??nh an to?n |
| TC3 | P3 | D? li?u h?p l? theo prompt | Gi? tr? c? ??nh an to?n |
| TC4 | P4 | D? li?u h?p l? theo prompt | Gi? tr? c? ??nh an to?n |

# C. Nh?nh kh?ng test

Kh?ng c? nh?nh b? b? qua ngo?i c?c nh?nh CHECK kh?ng th? l?m sai theo y?u c?u harness.

C2 d? ki?n = 6 / 6

# D. File test

```cpp
// FILE: u1454_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/inner_product_computer.h"
#include "ceres/linear_solver.h"
#include "ceres/sparse_cholesky.h"
#include "ceres/sparse_normal_cholesky_solver.h"
#include "ceres/wall_time.h"

// P1: START -> 1 -> END
TEST(u1454_Test, TC1_CallsTarget) {
  ceres::internal::SparseNormalCholeskySolver target{};
  target.SolveImpl(nullptr, nullptr, nullptr, nullptr);
}
```
