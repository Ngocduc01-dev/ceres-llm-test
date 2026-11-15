// FILE: u0332_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0332, PathP1) {
  double rho[3] = {};
  ceres::TrivialLoss target;
  target.Evaluate(1.0, rho);
}
