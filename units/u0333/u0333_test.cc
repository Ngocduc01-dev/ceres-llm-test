// FILE: u0333_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0333, PathP1) {
  double rho[3] = {};
  ceres::SoftLOneLoss target(1.0);
  target.Evaluate(1.0, rho);
}
