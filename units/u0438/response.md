# Unit u0438: `ceres::AutoDiffManifold::MinusJacobian`

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
// FILE: u0438_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_manifold.h"
struct EuclideanFunctor { template <typename T> bool Plus(const T* x,const T* d,T* out) const { out[0]=x[0]+d[0]; out[1]=x[1]+d[1]; out[2]=x[2]+d[2]; return true; } template <typename T> bool Minus(const T* y,const T* x,T* out) const { out[0]=y[0]-x[0]; out[1]=y[1]-x[1]; out[2]=y[2]-x[2]; return true; } };
TEST(Unit_u0438, MinusJacobian) { ceres::AutoDiffManifold<EuclideanFunctor,3,3> target; double x[3]={}, j[9]={}; target.MinusJacobian(x,j); }
```
