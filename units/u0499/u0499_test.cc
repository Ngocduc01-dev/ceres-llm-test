// FILE: u0499_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0499, PathP1) {
  double z_0[4] = {};
  double w_1[4] = {};
  double zw_2[4] = {};
  ceres::QuaternionProduct<double>(z_0, w_1, zw_2);
}
