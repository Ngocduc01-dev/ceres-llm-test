# Unit u0493: `ceres::AutoDiffManifold::PlusJacobian`

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
// FILE: u0493_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_manifold.h"
struct EuclideanFunctor2 { template <typename T> bool Plus(const T* x,const T* d,T* o) const { for(int i=0;i<3;++i)o[i]=x[i]+d[i]; return true; } template <typename T> bool Minus(const T* y,const T* x,T* o) const { for(int i=0;i<3;++i)o[i]=y[i]-x[i]; return true; } };
TEST(Unit_u0493, PlusJacobian) { ceres::AutoDiffManifold<EuclideanFunctor2,3,3> target; double x[3]={},j[9]={}; target.PlusJacobian(x,j); }
```
