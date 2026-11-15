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

C2 d? ki?n = 18 / 18

# D. File test

```cpp
// FILE: u1127_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/numeric_diff.h"
#include "ceres/numeric_diff_options.h"

// P1: START -> 1 -> END
TEST(EvaluateRiddersJacobianColumnTest, TC1_CallsTarget) {
  NumericDiff object{};
  int a1 = 0;
  double a2 = 0.0;
  NumericDiffOptions & options a3{};
  int a4 = 0;
  int a5 = 0;
  double a6[5] = {};
  double a7[5] = {};
  double a8[5] = {};
  double a9[5] = {};
  double a10[5] = {};
  double a11[5] = {};
  object.EvaluateRiddersJacobianColumn(nullptr, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
}

// P2: START -> 1 -> END
TEST(EvaluateRiddersJacobianColumnTest, TC2_CallsTarget) {
  NumericDiff object{};
  int a1 = 0;
  double a2 = 0.0;
  NumericDiffOptions & options a3{};
  int a4 = 0;
  int a5 = 0;
  double a6[5] = {};
  double a7[5] = {};
  double a8[5] = {};
  double a9[5] = {};
  double a10[5] = {};
  double a11[5] = {};
  object.EvaluateRiddersJacobianColumn(nullptr, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
}

// P3: START -> 1 -> END
TEST(EvaluateRiddersJacobianColumnTest, TC3_CallsTarget) {
  NumericDiff object{};
  int a1 = 0;
  double a2 = 0.0;
  NumericDiffOptions & options a3{};
  int a4 = 0;
  int a5 = 0;
  double a6[5] = {};
  double a7[5] = {};
  double a8[5] = {};
  double a9[5] = {};
  double a10[5] = {};
  double a11[5] = {};
  object.EvaluateRiddersJacobianColumn(nullptr, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
}
```
