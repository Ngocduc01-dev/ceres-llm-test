// FILE: u0500_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0500, PathP1) {
  double x_0[3] = {};
  double y_1[3] = {};
  double x_cross_y_2[3] = {};
  ceres::CrossProduct<double>(x_0, y_1, x_cross_y_2);
}
