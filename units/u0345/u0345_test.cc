// FILE: u0345_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0345, PathP1) {
  const double * arg_0 = nullptr;
  double * arg_1 = nullptr;
  ceres::QuaternionManifold target(arg_0, arg_1);
  target.MinusJacobian(nullptr, nullptr);
}
