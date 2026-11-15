// FILE: u0341_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0341, PathP1) {
  ceres::SubsetManifold target;
  target.TangentSize();
}
