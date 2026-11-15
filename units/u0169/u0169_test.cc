// FILE: u0169_test.cc
#include "gtest/gtest.h"
#include "ceres/line_manifold.h"

// TC1 - P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(LineManifoldPlusJacobian, P1_LinearPath) {
  ceres::LineManifold<3> manifold;
  const double x[6] = {0.7, 1.3, 0.9, 1.2, 0.6, 1.8};
  double jacobian[24] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  manifold.PlusJacobian(x, jacobian);
}
