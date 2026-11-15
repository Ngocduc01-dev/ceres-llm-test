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
// FILE: u0532_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_step_evaluator.h"

// Path P1 calls StepAccepted(const double cost, const double model_cost_change).
TEST(Unitu0532, CallsTarget) {
  object.StepAccepted(1.0, 1.0);
}

// Path P2 calls StepAccepted(const double cost, const double model_cost_change) on the alternate CFG path.
TEST(Unitu0532, CallsTargetAlternate) {
  object.StepAccepted(1.0, 1.0);
}
```
