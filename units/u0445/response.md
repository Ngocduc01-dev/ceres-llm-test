# Unit u0445: `ceres::internal::ArraySelector::ArraySelector<type-parameter-0-0, num_elements, max_num_elements_on_stack, false, true>`

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
// FILE: u0445_test.cc
#include "gtest/gtest.h"
TEST(Unit_u0445, Constructor) {
  ceres::internal::ArraySelector<int, 1, 20> target(1);
}
```
