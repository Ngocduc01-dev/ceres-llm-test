# Unit u0406
## A. Test paths

| Path | ???ng ?i (theo s? node) | C?c nh?nh ?i qua |
|---|---|---|
| P1 | START ? 1 ? END | Kh?ng c? ?i?m r? nh?nh trong CFG. |

## B. B? test case

| Test | Path | Kho?ng gi? tr? ??u v?o | Gi? tr? ?? ch?n |
|---|---|---|---|
| TC1 | P1 | Theo ch? k? `Chunk(int start)` | Gi? tr? h?p l? trong file test |

## C. Nh?nh kh?ng test

Kh?ng c? nh?nh ?i?u khi?n. C2 d? ki?n = 0 / 0.

## D. File test

```cpp
// FILE: u0406_test.cc
#include "gtest/gtest.h"
#include "ceres/schur_eliminator.h"
// Path P1: START -> 1 -> END.
TEST(Unit_u0406, PathP1) { ceres::internal::SchurEliminator<1,1,1>::Chunk target(1); }
```
