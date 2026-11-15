// FILE: u0343_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0343, PathP1) {
  const double * arg_0 = nullptr;
  double * arg_1 = nullptr;
  ceres::QuaternionManifold target(arg_0, arg_1);
  target.PlusJacobian(nullptr, nullptr);
}
