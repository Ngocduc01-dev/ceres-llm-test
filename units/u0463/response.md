# Unit u0463: `ceres::SphereManifold::Plus`

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
// FILE: u0463_test.cc
#include "gtest/gtest.h"
#include "ceres/sphere_manifold.h"
TEST(Unit_u0463, Plus) { ceres::SphereManifold<4> target; double x[4]={1,0,0,0}, d[3]={}, out[4]={}; target.Plus(x,d,out); }
```
