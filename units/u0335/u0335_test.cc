// FILE: u0335_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0335, PathP1) {
  double rho[3] = {};
  ceres::ArctanLoss target(1.0);
  target.Evaluate(1.0, rho);
}
