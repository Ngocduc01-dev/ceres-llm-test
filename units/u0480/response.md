# Unit u0480: `ceres::internal::ParameterBlock::UpperBound`

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
// FILE: u0480_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
TEST(Unit_u0480, UpperBound) { double state[1]={}; ceres::internal::ParameterBlock target(state,1,0); target.UpperBound(0); }
```
