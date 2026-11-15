// FILE: u0183_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EuclideanManifoldMinus, P1_SinglePath) {
  ceres::EuclideanManifold<ceres::DYNAMIC> manifold(3);
  const double x[3] = {1.5, -2.0, 4.0};
  const double y[3] = {0.5, 3.0, -1.0};
  double y_minus_x[3] = {0.0, 0.0, 0.0};
  manifold.Minus(y, x, y_minus_x);
}
