// FILE: u0463_test.cc
#include "gtest/gtest.h"
#include "ceres/sphere_manifold.h"
TEST(Unit_u0463, Plus) { ceres::SphereManifold<4> target; double x[4]={1,0,0,0}, d[3]={}, out[4]={}; target.Plus(x,d,out); }
