// FILE: u0493_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_manifold.h"
struct EuclideanFunctor2 { template <typename T> bool Plus(const T* x,const T* d,T* o) const { for(int i=0;i<3;++i)o[i]=x[i]+d[i]; return true; } template <typename T> bool Minus(const T* y,const T* x,T* o) const { for(int i=0;i<3;++i)o[i]=y[i]-x[i]; return true; } };
TEST(Unit_u0493, PlusJacobian) { ceres::AutoDiffManifold<EuclideanFunctor2,3,3> target; double x[3]={},j[9]={}; target.PlusJacobian(x,j); }
