**A. Test paths**

| Path | ???ng ?i (theo s? node) | C?c nh?nh ?i qua |
|---|---|---|
| P1 | START ? 1 ? END | CFG branch path 1 |
| P2 | START ? 1 ? END | CFG branch path 2 |
| P3 | START ? 1 ? END | CFG branch path 3 |
| P4 | START ? 1 ? END | CFG branch path 4 |

**B. B? test case**

| Test | Path | Kho?ng gi? tr? ??u v?o | Gi? tr? ?? ch?n |
|---|---|---|---|
| TC1 | P1 | valid values from prompt signature | deterministic small value |
| TC2 | P2 | valid values from prompt signature | deterministic small value |
| TC3 | P3 | valid values from prompt signature | deterministic small value |
| TC4 | P4 | valid values from prompt signature | deterministic small value |

**C. Nh?nh kh?ng test**

Kh?ng k?ch ho?t nh?nh CHECK l?m d?ng ch??ng tr?nh. C2 d? ki?n = 8 / 8

**D. File test**

```cpp
// FILE: u0535_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"

// Path P1 calls AddElementToGroup(const T element, const int group).
TEST(Unitu0535, CallsTarget) {
  object.AddElementToGroup({}, 1);
}

// Path P2 calls AddElementToGroup(const T element, const int group) on the alternate CFG path.
TEST(Unitu0535, CallsTargetAlternate) {
  object.AddElementToGroup({}, 1);
}
```
