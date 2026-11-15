# Unit u0440: `ceres::Grid1D::Grid1D<T, kDataDimension, kInterleaved>`

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
// FILE: u0440_test.cc
#include "gtest/gtest.h"
TEST(Unit_u0440, Constructor) {
  const double data[2] = {0.0, 1.0};
  ceres::Grid1D<double, 2> target(data, 0, 2);
}
```
