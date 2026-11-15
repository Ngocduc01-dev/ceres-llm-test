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
// FILE: u0505_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_col_sparse_matrix_utils.h"

namespace ceres {
namespace internal {
// Path P1 calls SolveUpperTriangularTransposeInPlace(IntegerType num_cols, const IntegerType* rows, const IntegerType* cols, const double* values, double* rhs_and_solution).
TEST(Unitu0505, CallsTarget) {
  double rows_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double cols_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double values_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double rhs_and_solution_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  SolveUpperTriangularTransposeInPlace(1, rows_data, cols_data, values_data, rhs_and_solution_data);
}
}  // namespace internal
}  // namespace ceres
```
