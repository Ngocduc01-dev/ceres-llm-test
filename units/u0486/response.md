# Unit u0486: `ceres::internal::SetSummaryFinalCost`

## A. Test paths

| Path | ???ng ?i | Nh?nh |
|---|---|---|
| P1 | START ? 1 ? END | Theo CFG trong prompt. |

## B. B? test case

| Test | Path | D? li?u |
|---|---|---|
| TC1 | P1 | D? li?u h?p l?, k?ch th??c nh?. |

## C. Nh?nh kh?ng test

Kh?ng c? t?nh l?m sai CHECK. C2 d? ki?n theo cfg.txt.

## D. File test
```cpp
// FILE: u0486_test.cc
#include "gtest/gtest.h"
#include "ceres/iteration_callback.h"
#include "ceres/solver_utils.h"
TEST(Unit_u0486, SetSummaryFinalCost) { ceres::Solver::Summary summary; ceres::internal::SetSummaryFinalCost(&summary); }
```
