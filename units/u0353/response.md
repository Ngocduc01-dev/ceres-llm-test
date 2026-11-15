# Unit u0353
## A. Test paths

| Path | ???ng ?i (theo s? node) | C?c nh?nh ?i qua |
|---|---|---|
| P1 | START ? 1 ? END | Kh?ng c? ?i?m r? nh?nh trong CFG. |

## B. B? test case

| Test | Path | Kho?ng gi? tr? ??u v?o | Gi? tr? ?? ch?n |
|---|---|---|---|
| TC1 | P1 | Theo ch? k? `void hash_mix(uint64_t & a, uint64_t & b, uint64_t & c)` | Gi? tr? h?p l? trong file test |

## C. Nh?nh kh?ng test

Kh?ng c? nh?nh ?i?u khi?n. C2 d? ki?n = 0 / 0.

## D. File test

```cpp
// FILE: u0353_test.cc
#include "gtest/gtest.h"
#include "ceres/pair_hash.h"
// Path P1: START -> 1 -> END.
TEST(Unit_u0353, PathP1) { uint64_t a=1,b=2,c=3; ceres::internal::hash_mix(a,b,c); }
```
