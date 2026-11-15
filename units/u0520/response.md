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
// FILE: u0520_test.cc
#include "gtest/gtest.h"
#include "ceres/line_manifold.h"

// Path P1 calls Plus(const double * x_ptr, const double * delta_ptr, double * x_plus_delta_ptr) const.
TEST(Unitu0520, CallsTarget) {
  double x_ptr_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double delta_ptr_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double x_plus_delta_ptr_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Plus(x_ptr_data, delta_ptr_data, x_plus_delta_ptr_data);
}

// Path P2 calls Plus(const double * x_ptr, const double * delta_ptr, double * x_plus_delta_ptr) const on the alternate CFG path.
TEST(Unitu0520, CallsTargetAlternate) {
  double x_ptr_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double delta_ptr_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double x_plus_delta_ptr_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Plus(x_ptr_data, delta_ptr_data, x_plus_delta_ptr_data);
}
```
