# Unit u0495: `ceres::internal::Take0thOrderPart`

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
// FILE: u0495_test.cc
#include "gtest/gtest.h"
TEST(Unit_u0495, Take0thOrderPart) {
  ceres::Jet<double, 2> source[1] = {ceres::Jet<double, 2>(1.0)};
  double destination = 0.0;
  ceres::internal::Take0thOrderPart(1, source, destination);
}
```
