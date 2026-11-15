// FILE: u0342_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0342, PathP1) {
  const double * arg_0 = nullptr;
  const double * arg_1 = nullptr;
  double * arg_2 = nullptr;
  ceres::QuaternionManifold target(arg_0, arg_1, arg_2);
  target.Plus(nullptr, nullptr, nullptr);
}
