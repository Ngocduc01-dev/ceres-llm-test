// FILE: u0170_test.cc
#include "gtest/gtest.h"
#include "ceres/line_manifold.h"

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(LineManifoldMinusTest, TC1_P1_SinglePath) {
  ceres::LineManifold<3> manifold;

  const double y[6] = {1.5, -2.0, 0.5, 3.0, 1.0, -1.5};
  const double x[6] = {0.5, 1.0, -1.0, 2.0, -3.0, 1.5};
  double y_minus_x[4] = {0.0, 0.0, 0.0, 0.0};

  (void)manifold.Minus(y, x, y_minus_x);
}
