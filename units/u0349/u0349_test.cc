// FILE: u0349_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0349, PathP1) {
  const double * arg_0 = nullptr;
  double * arg_1 = nullptr;
  ceres::EigenQuaternionManifold target(arg_0, arg_1);
  target.MinusJacobian(nullptr, nullptr);
}
