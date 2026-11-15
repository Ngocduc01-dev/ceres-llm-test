// FILE: u0344_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"
// Path P1: START -> 1 -> END.
TEST(Unit_u0344, PathP1) { double x[4] = {1,0,0,0}; double d[3] = {0,0,0}; double out[4] = {}; ceres::QuaternionManifold target; target.Minus(x, d, out); }
