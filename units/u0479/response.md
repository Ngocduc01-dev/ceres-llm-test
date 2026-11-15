# Unit u0479: `ceres::internal::ParameterBlock::GetState`

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
// FILE: u0479_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
TEST(Unit_u0479, GetState) { double state[2]={1,2}, out[2]={}; ceres::internal::ParameterBlock target(state,2,0); target.GetState(out); }
```
