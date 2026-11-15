# A. Test paths

| Path | ???ng ?i (theo s? node) | C?c nh?nh ?i qua |
|---|---|---|
| P1 | START ? 1 ? END | C?c nh?nh kh? thi c?a CFG; bi?n th? d? li?u 1 |

# B. B? test case

| Test | Path | Kho?ng gi? tr? ??u v?o | Gi? tr? ?? ch?n |
|---|---|---|---|
| TC1 | P1 | Tham s? nh?, h?p l? theo ch? k? | Gi? tr? m?c ??nh an to?n |

# C. Nh?nh kh?ng test

Kh?ng c? t?nh ?i v?o c?c nh?nh CHECK l?m ch??ng tr?nh d?ng; c?c nh?nh kh?ng kh? thi ???c ghi nh?n theo CFG.

C2 d? ki?n = 1 / 1

# D. File test

```cpp
// FILE: u0859_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/manifold.h"
#include "ceres/numeric_diff_options.h"
#include "ceres/gradient_checking_cost_function.h"

// P1: START -> 1 -> END
TEST(CreateGradientCheckingCostFunctionTest, TC1_CallsTarget) {
  double a2 = 0.0;
  double a3 = 0.0;
  std::string & extra_info a4;
  ceres::internal::CreateGradientCheckingCostFunction(nullptr, nullptr, a2, a3, a4, nullptr);
}
```
