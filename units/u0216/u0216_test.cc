// FILE: u0216_test.cc
#include "gtest/gtest.h"
#include "ceres/sphere_manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(SphereManifoldMinusTest, TC1_P1_StaticSize2) {
  ceres::SphereManifold<2> manifold;
  const double x[2] = {0.6, 0.8};
  const double y[2] = {-0.28, 0.96};
  double y_minus_x[1] = {0.0};
  manifold.Minus(y, x, y_minus_x);
}
