**A. Test paths**

| Path | ???ng ?i (theo s? node) | C?c nh?nh ?i qua |
|---|---|---|
| P1 | START ? 1 ? END | CFG branch path 1 |
| P2 | START ? 1 ? END | CFG branch path 2 |
| P3 | START ? 1 ? END | CFG branch path 3 |

**B. B? test case**

| Test | Path | Kho?ng gi? tr? ??u v?o | Gi? tr? ?? ch?n |
|---|---|---|---|
| TC1 | P1 | valid values from prompt signature | deterministic small value |
| TC2 | P2 | valid values from prompt signature | deterministic small value |
| TC3 | P3 | valid values from prompt signature | deterministic small value |

**C. Nh?nh kh?ng test**

Kh?ng k?ch ho?t nh?nh CHECK l?m d?ng ch??ng tr?nh. C2 d? ki?n = 6 / 6

**D. File test**

```cpp
// FILE: u0743_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/internal/numeric_diff.h"
#include "ceres/internal/variadic_evaluate.h"
#include "ceres/numeric_diff_first_order_function.h"

// Path P1 calls Evaluate(const double *const parameters, double * cost, double * gradient) const.
TEST(Unitu0743, CallsTarget) {
  double parameters_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double cost_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double gradient_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Evaluate(parameters_data, cost_data, gradient_data);
}

// Path P2 calls Evaluate(const double *const parameters, double * cost, double * gradient) const on the alternate CFG path.
TEST(Unitu0743, CallsTargetAlternate) {
  double parameters_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double cost_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double gradient_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Evaluate(parameters_data, cost_data, gradient_data);
}
```
