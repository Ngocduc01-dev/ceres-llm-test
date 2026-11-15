# Unit u0414: `ceres::internal::SparseCholesky::~SparseCholesky`

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
// FILE: u0414_test.cc
#include <memory>
#include "gtest/gtest.h"
#include "ceres/sparse_cholesky.h"
TEST(Unit_u0414, Destruction) { std::unique_ptr<ceres::internal::SparseCholesky> target; }
```
