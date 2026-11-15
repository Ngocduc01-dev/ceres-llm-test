// FILE: u0471_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: START -> 1 -> 2 -> END (node 1: đúng)
// Path P1: START -> CFG nodes -> END.
TEST(TukeyLossEvaluateTest, InlierRegion) {
  ceres::TukeyLoss loss(2.0);
  double rho[3] = {0.0, 0.0, 0.0};
  loss.Evaluate(1.5, rho);
}

// P2: START -> 1 -> 3 -> END (node 1: sai)
// Path P1: START -> CFG nodes -> END.
TEST(TukeyLossEvaluateTest, OutlierRegion) {
  ceres::TukeyLoss loss(2.0);
  double rho[3] = {0.0, 0.0, 0.0};
  loss.Evaluate(7.3, rho);
}
