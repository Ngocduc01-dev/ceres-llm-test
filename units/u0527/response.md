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
// FILE: u0527_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_invoke.h"

// Path P1 calls Finished(int num_jobs_finished).
TEST(Unitu0527, CallsTarget) {
  object.Finished(1);
}

// Path P2 calls Finished(int num_jobs_finished) on the alternate CFG path.
TEST(Unitu0527, CallsTargetAlternate) {
  object.Finished(1);
}
```
