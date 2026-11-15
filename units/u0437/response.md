# Unit u0437: `ceres::AutoDiffCostFunction::Evaluate`

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
// FILE: u0437_test.cc
#include <memory>
#include "gtest/gtest.h"
#include "ceres/autodiff_cost_function.h"
struct BinaryScalarCost { template <typename T> bool operator()(const T* x, const T* y, T* r) const { r[0] = x[0] + y[0]; return true; } };
TEST(Unit_u0437, Evaluate) { auto target = std::make_unique<ceres::AutoDiffCostFunction<BinaryScalarCost, 1, 2, 2>>(new BinaryScalarCost); double x[2]={}, y[2]={}, r[1]={}; double* p[]={x,y}; target->Evaluate(p,r,nullptr); }
```
