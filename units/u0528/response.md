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
// FILE: u0528_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_invoke.h"

namespace ceres {
namespace internal {
// Path P1 calls InvokeOnSegment(int thread_id, std::tuple<int, int> range, F&& function).
TEST(Unitu0528, CallsTarget) {
  InvokeOnSegment(1, 1, {});
}
}  // namespace internal
}  // namespace ceres
```
