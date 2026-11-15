// FILE: u0469_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: START -> 1 -> 2 -> END (node 1: đúng)
TEST(HuberLossEvaluate, OutlierRegion) {
  ceres::HuberLoss loss(2.0);  // b_ = 4.0
  double rho[3] = {0.0, 0.0, 0.0};
  loss.Evaluate(7.3, rho);     // s > b_
}

// P2: START -> 1 -> 3 -> END (node 1: sai)
TEST(HuberLossEvaluate, InlierRegion) {
  ceres::HuberLoss loss(2.0);  // b_ = 4.0
  double rho[3] = {0.0, 0.0, 0.0};
  loss.Evaluate(2.1, rho);     // s <= b_
}
