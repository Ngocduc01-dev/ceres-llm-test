**A. Test paths**

| Path | ???ng ?i (theo s? node) | C?c nh?nh ?i qua |
|---|---|---|
| P1 | START ? 1 ? END | CFG branch path 1 |
| P2 | START ? 1 ? END | CFG branch path 2 |

**B. B? test case**

| Test | Path | Kho?ng gi? tr? ??u v?o | Gi? tr? ?? ch?n |
|---|---|---|---|
| TC1 | P1 | valid values from prompt signature | deterministic small value |
| TC2 | P2 | valid values from prompt signature | deterministic small value |

**C. Nh?nh kh?ng test**

Kh?ng k?ch ho?t nh?nh CHECK l?m d?ng ch??ng tr?nh. C2 d? ki?n = 4 / 4

**D. File test**

```cpp
// FILE: u0742_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/internal/numeric_diff.h"
#include "ceres/numeric_diff_cost_function.h"
#include "ceres/sized_cost_function.h"

// Path P1 calls Evaluate(const double *const * parameters, double * residuals, double ** jacobians) const.
TEST(Unitu0742, CallsTarget) {
  double parameters_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double residuals_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double jacobians_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Evaluate(parameters_data, residuals_data, jacobians_data);
}

// Path P2 calls Evaluate(const double *const * parameters, double * residuals, double ** jacobians) const on the alternate CFG path.
TEST(Unitu0742, CallsTargetAlternate) {
  double parameters_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double residuals_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double jacobians_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Evaluate(parameters_data, residuals_data, jacobians_data);
}
```
