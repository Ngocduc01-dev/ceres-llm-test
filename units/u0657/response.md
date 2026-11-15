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
// FILE: u0657_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_cholesky.h"

// Path P1 calls Factorize(const int num_cols, double * lhs, std::string * message).
TEST(Unitu0657, CallsTarget) {
  double lhs_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double message_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Factorize(1, lhs_data, message_data);
}
```
