# A. Test paths

| Path | ???ng ?i (theo s? node) | C?c nh?nh ?i qua |
|---|---|---|
| P1 | START ? 1 ? END | C?c nh?nh kh? thi c?a CFG; bi?n th? d? li?u 1 |
| P2 | START ? 1 ? END | C?c nh?nh kh? thi c?a CFG; bi?n th? d? li?u 2 |

# B. B? test case

| Test | Path | Kho?ng gi? tr? ??u v?o | Gi? tr? ?? ch?n |
|---|---|---|---|
| TC1 | P1 | Tham s? nh?, h?p l? theo ch? k? | Gi? tr? m?c ??nh an to?n |
| TC2 | P2 | Tham s? nh?, h?p l? theo ch? k? | Gi? tr? m?c ??nh an to?n |

# C. Nh?nh kh?ng test

Kh?ng c? t?nh ?i v?o c?c nh?nh CHECK l?m ch??ng tr?nh d?ng; c?c nh?nh kh?ng kh? thi ???c ghi nh?n theo CFG.

C2 d? ki?n = 2 / 2

# D. File test

```cpp
// FILE: u0969_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluator.h"
#include "ceres/line_search_minimizer.h"
#include "ceres/line_search_minimizer.cc"

// P1: START -> 1 -> END
TEST(EvaluateGradientNormsTest, TC1_CallsTarget) {
  Vector & x a1{};
  EvaluateGradientNorms(nullptr, a1, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(EvaluateGradientNormsTest, TC2_CallsTarget) {
  Vector & x a1{};
  EvaluateGradientNorms(nullptr, a1, nullptr, nullptr);
}
```
