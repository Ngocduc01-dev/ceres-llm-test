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
// FILE: u0516_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/autodiff.h"

namespace ceres {
namespace internal {
// Path P1 calls Take1stOrderPart(const int M, const JetT* src, T* dst).
TEST(Unitu0516, CallsTarget) {
  double src_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double dst_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  Take1stOrderPart(1, src_data, dst_data);
}
}  // namespace internal
}  // namespace ceres
```
