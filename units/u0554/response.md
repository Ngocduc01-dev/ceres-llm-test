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
// FILE: u0554_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/householder_vector.h"

namespace ceres {
namespace internal {
// Path P1 calls ComputeHouseholderVector(const XVectorType& x, Eigen::Matrix<Scalar, N, 1>* v, Scalar* beta).
TEST(Unitu0554, CallsTarget) {
  double v_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double beta_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  ComputeHouseholderVector({}, v_data, beta_data);
}

// Path P2 calls ComputeHouseholderVector(const XVectorType& x, Eigen::Matrix<Scalar, N, 1>* v, Scalar* beta) on the alternate CFG path.
TEST(Unitu0554, CallsTargetAlternate) {
  double v_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double beta_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  ComputeHouseholderVector({}, v_data, beta_data);
}
}  // namespace internal
}  // namespace ceres
```
