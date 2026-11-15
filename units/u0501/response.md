**A. Test paths**

| Path | ???ng ?i (theo s? node) | C?c nh?nh ?i qua |
|---|---|---|
| P1 | START ? 1 ? END | CFG branch path 1 |

**B. B? test case**

| Test | Path | Kho?ng gi? tr? ??u v?o | Gi? tr? ?? ch?n |
|---|---|---|---|
| TC1 | P1 | valid values from prompt signature | deterministic small value |

**C. Nh?nh kh?ng test**

Kh?ng k?ch ho?t nh?nh CHECK l?m d?ng ch??ng tr?nh. C2 d? ki?n = 2 / 2

**D. File test**

```cpp
// FILE: u0501_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

namespace ceres {
// Path P1 calls AngleAxisRotatePoint(const T angle_axis[3], const T pt[3], T result[3]).
TEST(Unitu0501, CallsTarget) {
  double angle_axis_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double pt_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double result_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  AngleAxisRotatePoint(angle_axis_data, pt_data, result_data);
}
}  // namespace ceres
```
