// FILE: u0472_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// Path P1: START -> 1 → 2 → END (rho_ is null).
TEST(Unit_u0472, PathP1) {
  double rho[3] = {};
  ceres::ScaledLoss target(nullptr, 2.0, ceres::DO_NOT_TAKE_OWNERSHIP);
  target.Evaluate(1.0, rho);
}

// Path P2: START -> 1 → 3 → END (rho_ is non-null).
TEST(Unit_u0472, PathP2) {
  double rho[3] = {};
  ceres::TrivialLoss inner;
  ceres::ScaledLoss target(&inner, 2.0, ceres::DO_NOT_TAKE_OWNERSHIP);
  target.Evaluate(1.0, rho);
}
