// FILE: u0346_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EigenQuaternionManifoldPlus, TC1_SinglePath) {
  ceres::EigenQuaternionManifold manifold;
  const double x[4] = {0.1, 0.2, 0.3, 0.9};
  const double delta[3] = {0.05, -0.1, 0.2};
  double x_plus_delta[4] = {0.0, 0.0, 0.0, 0.0};
  manifold.Plus(x, delta, x_plus_delta);
}
