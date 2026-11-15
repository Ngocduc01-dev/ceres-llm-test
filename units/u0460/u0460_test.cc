// FILE: u0460_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0460, PathP1) {
  double q_0[4] = {};
  double pt_1[3] = {};
  double result_2[3] = {};
  ceres::UnitQuaternionRotatePoint<double>(q_0, pt_1, result_2);
}
