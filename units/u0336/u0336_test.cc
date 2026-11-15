// FILE: u0336_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0336, PathP1) {
  double rho[3] = {};
  ceres::TrivialLoss f;
  ceres::TrivialLoss g;
  ceres::ComposedLoss target(&f, ceres::DO_NOT_TAKE_OWNERSHIP,
                             &g, ceres::DO_NOT_TAKE_OWNERSHIP);
  target.Evaluate(1.0, rho);
}
