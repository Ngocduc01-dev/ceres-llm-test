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
// FILE: u0649_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_dense_matrix.h"
#include "ceres/block_random_access_matrix.h"

// Path P1 calls GetCell(const int row_block_id, const int col_block_id, int * row, int * col, int * row_stride, int * col_stride).
TEST(Unitu0649, CallsTarget) {
  double row_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double col_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double row_stride_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double col_stride_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.GetCell(1, 1, row_data, col_data, row_stride_data, col_stride_data);
}
```
