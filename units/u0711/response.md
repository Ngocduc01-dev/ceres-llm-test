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
// FILE: u0711_test.cc
#include "gtest/gtest.h"
#include "ceres/iteration_callback.h"
#include "ceres/gradient_checking_cost_function.h"

// Path P1 calls operator()(const IterationSummary &).
TEST(Unitu0711, CallsTarget) {
  object.operator({});
}
```
