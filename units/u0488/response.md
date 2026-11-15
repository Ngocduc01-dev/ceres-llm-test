# Unit u0488: `ceres::STLDeleteUniqueContainerPointers`

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
// FILE: u0488_test.cc
#include <vector>
#include "gtest/gtest.h"
#include "ceres/stl_util.h"
TEST(Unit_u0488, DeleteUniquePointers) {
  std::vector<int*> values;
  ceres::STLDeleteUniqueContainerPointers(values.begin(), values.end());
}
```
