// FILE: u0347_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0347, PathP1) {
  const double * arg_0 = nullptr;
  double * arg_1 = nullptr;
  ceres::EigenQuaternionManifold target(arg_0, arg_1);
  target.PlusJacobian(nullptr, nullptr);
}
