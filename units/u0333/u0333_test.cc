// FILE: u0333_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0333, PathP1) {
   double_1[3] = {};
  double arg_0 = 1.0;
  double arg_1 = 1.0;
  ceres::SoftLOneLoss target(arg_0, arg_1);
  target.Evaluate(1.0, double_1);
}
