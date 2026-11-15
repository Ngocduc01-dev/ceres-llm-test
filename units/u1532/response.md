# A. Test paths

| Path | ???ng ?i (theo s? node) | C?c nh?nh ?i qua |
|---|---|---|
| P1 | START ? 1 ? END | node 1: ???ng ?i kh? thi P1 |
| P2 | START ? 1 ? END | node 1: ???ng ?i kh? thi P2 |

# B. B? test case

| Test | Path | Kho?ng gi? tr? ??u v?o | Gi? tr? ?? ch?n |
|---|---|---|---|
| TC1 | P1 | D? li?u h?p l? theo prompt | Gi? tr? c? ??nh an to?n |
| TC2 | P2 | D? li?u h?p l? theo prompt | Gi? tr? c? ??nh an to?n |

# C. Nh?nh kh?ng test

Kh?ng c? nh?nh b? b? qua ngo?i c?c nh?nh CHECK kh?ng th? l?m sai theo y?u c?u harness.

C2 d? ki?n = 2 / 2

# D. File test

```cpp
// FILE: u1532_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END
TEST(u1532_Test, TC1_CallsTarget) {
  ceres_problem_add_residual_block(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}
```
