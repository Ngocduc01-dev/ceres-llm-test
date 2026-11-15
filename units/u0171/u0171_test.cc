// FILE: u0171_test.cc
#include "gtest/gtest.h"
#include "ceres/line_manifold.h"

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(LineManifoldMinusJacobian, StraightLinePath) {
  ceres::LineManifold<3> manifold;
  double x[6] = {0.3, -0.7, 0.5, 0.48, 0.64, 0.6};
  double jacobian[24] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  manifold.MinusJacobian(x, jacobian);
}
