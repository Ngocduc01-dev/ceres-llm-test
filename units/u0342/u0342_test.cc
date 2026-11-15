// FILE: u0342_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(QuaternionManifoldPlusTest, TC1_StraightLinePath) {
  ceres::QuaternionManifold manifold;
  const double x[4] = {1.0, 0.0, 0.0, 0.0};
  const double delta[3] = {0.3, -0.2, 0.5};
  double x_plus_delta[4] = {0.0, 0.0, 0.0, 0.0};
  manifold.Plus(x, delta, x_plus_delta);
}
