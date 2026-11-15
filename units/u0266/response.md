# A. Test paths

| Path | ???ng ?i (theo s? node) | C?c nh?nh ?i qua |
|---|---|---|
| P1 | START ? 1 ? END | Kh?ng c? ?i?m r? nh?nh; node 1 ???c th?c hi?n. |

# B. B? test case

| Test | Path | Kho?ng gi? tr? ??u v?o | Gi? tr? ?? ch?n |
|---|---|---|---|
| TC1 | P1 | D? li?u h?p l? t?i thi?u theo ch? k? c?a unit. | Gi? tr? c? ??nh trong m? test. |

# C. Nh?nh kh?ng test

Kh?ng c? nh?nh ?i?u khi?n trong CFG c?a unit. C2 d? ki?n = 0 / 0.

# D. File test

```cpp
// FILE: u0266_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"
#include "ceres/compressed_row_sparse_matrix.h"

TEST(Unit_u0266, PathP1) {
  // Path P1: START -> 1 -> END.
  ceres::internal::CompressedRowSparseMatrix object(1, 1, 1);
  object.mutable_row_blocks();
}
```
