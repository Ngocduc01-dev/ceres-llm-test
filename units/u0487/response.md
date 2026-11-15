# Unit u0487: `ceres::STLDeleteContainerPointers`

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
// FILE: u0487_test.cc
#include <vector>
#include "gtest/gtest.h"
#include "ceres/stl_util.h"
TEST(Unit_u0487, DeletePointers) {
  std::vector<int*> values;
  ceres::STLDeleteContainerPointers(values.begin(), values.end());
}
```
