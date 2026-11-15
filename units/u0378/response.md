# Unit u0378
## A. Test paths

| Path | ???ng ?i (theo s? node) | C?c nh?nh ?i qua |
|---|---|---|
| P1 | START ? 1 ? END | Kh?ng c? ?i?m r? nh?nh trong CFG. |

## B. B? test case

| Test | Path | Kho?ng gi? tr? ??u v?o | Gi? tr? ?? ch?n |
|---|---|---|---|
| TC1 | P1 | Theo ch? k? `const std::vector<int> & f_cols_partition() const` | Gi? tr? h?p l? trong file test |

## C. Nh?nh kh?ng test

Kh?ng c? nh?nh ?i?u khi?n. C2 d? ki?n = 0 / 0.

## D. File test

```cpp
// FILE: u0378_test.cc
#include "gtest/gtest.h"
#include "ceres/partitioned_matrix_view.h"
#include "ceres/block_sparse_matrix.h"
// Path P1: START -> 1 -> END.
TEST(Unit_u0378, PathP1) { ceres::LinearSolver::Options options; ceres::internal::CompressedRowBlockStructure* bs = new ceres::internal::CompressedRowBlockStructure; ceres::internal::BlockSparseMatrix matrix(bs); ceres::internal::PartitionedMatrixView<2> target(options, matrix); target.f_cols_partition(); }
```
