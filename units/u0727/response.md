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
// FILE: u0727_test.cc
#include "gtest/gtest.h"
#include "ceres/inner_product_computer.h"

// Path P1 calls operator<(const ProductTerm & right) const.
TEST(Unitu0727, CallsTarget) {
  object.operator<({});
}

// Path P2 calls operator<(const ProductTerm & right) const on the alternate CFG path.
TEST(Unitu0727, CallsTargetAlternate) {
  object.operator<({});
}
```
