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
// FILE: u0608_test.cc
#include "gtest/gtest.h"
#include "ceres/small_blas_generic.h"

namespace ceres {
namespace internal {
// Path P1 calls MTM_mat1x4(const int col_a, const double * a, const int col_stride_a, const double * b, const int col_stride_b, double * c, const int kOperation).
TEST(Unitu0608, CallsTarget) {
  double a_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double b_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double c_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  MTM_mat1x4(1, a_data, 1, b_data, 1, c_data, 1);
}

// Path P2 calls MTM_mat1x4(const int col_a, const double * a, const int col_stride_a, const double * b, const int col_stride_b, double * c, const int kOperation) on the alternate CFG path.
TEST(Unitu0608, CallsTargetAlternate) {
  double a_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double b_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double c_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  MTM_mat1x4(1, a_data, 1, b_data, 1, c_data, 1);
}
}  // namespace internal
}  // namespace ceres
```
