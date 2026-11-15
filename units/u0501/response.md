# Unit u0501: `ceres::AngleAxisRotatePoint`

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
// FILE: u0501_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"
TEST(Unit_u0501, Rotate) { double angle_axis[3]={1,2,3}, point[3]={1,2,3}, result[3]={}; ceres::AngleAxisRotatePoint(angle_axis,point,result); }
```
