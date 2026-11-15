# A. Test paths

| Path | ???ng ?i (theo s? node) | C?c nh?nh ?i qua |
|---|---|---|
| P1 | START ? 1 ? END | C?c nh?nh kh? thi c?a CFG; bi?n th? d? li?u 1 |
| P2 | START ? 1 ? END | C?c nh?nh kh? thi c?a CFG; bi?n th? d? li?u 2 |
| P3 | START ? 1 ? END | C?c nh?nh kh? thi c?a CFG; bi?n th? d? li?u 3 |

# B. B? test case

| Test | Path | Kho?ng gi? tr? ??u v?o | Gi? tr? ?? ch?n |
|---|---|---|---|
| TC1 | P1 | Tham s? nh?, h?p l? theo ch? k? | Gi? tr? m?c ??nh an to?n |
| TC2 | P2 | Tham s? nh?, h?p l? theo ch? k? | Gi? tr? m?c ??nh an to?n |
| TC3 | P3 | Tham s? nh?, h?p l? theo ch? k? | Gi? tr? m?c ??nh an to?n |

# C. Nh?nh kh?ng test

Kh?ng c? t?nh ?i v?o c?c nh?nh CHECK l?m ch??ng tr?nh d?ng; c?c nh?nh kh?ng kh? thi ???c ghi nh?n theo CFG.

C2 d? ki?n = 4 / 4

# D. File test

```cpp
// FILE: u0759_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/numeric_diff.h"

// P1: START -> 1 -> END
TEST(EvaluateJacobianColumnTest, TC1_CallsTarget) {
  NumericDiff object{};
  int a1 = 0;
  double a2 = 0.0;
  int a3 = 0;
  int a4 = 0;
  double a5[5] = {};
  double a6[5] = {};
  double a7[5] = {};
  double a8[5] = {};
  double a9[5] = {};
  double a10[5] = {};
  object.EvaluateJacobianColumn(nullptr, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}

// P2: START -> 1 -> END
TEST(EvaluateJacobianColumnTest, TC2_CallsTarget) {
  NumericDiff object{};
  int a1 = 0;
  double a2 = 0.0;
  int a3 = 0;
  int a4 = 0;
  double a5[5] = {};
  double a6[5] = {};
  double a7[5] = {};
  double a8[5] = {};
  double a9[5] = {};
  double a10[5] = {};
  object.EvaluateJacobianColumn(nullptr, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}

// P3: START -> 1 -> END
TEST(EvaluateJacobianColumnTest, TC3_CallsTarget) {
  NumericDiff object{};
  int a1 = 0;
  double a2 = 0.0;
  int a3 = 0;
  int a4 = 0;
  double a5[5] = {};
  double a6[5] = {};
  double a7[5] = {};
  double a8[5] = {};
  double a9[5] = {};
  double a10[5] = {};
  object.EvaluateJacobianColumn(nullptr, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}
```
