// FILE: u0181_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EuclideanManifoldPlusJacobian, TC1_P1_SinglePath) {
  ceres::EuclideanManifold<ceres::DYNAMIC> manifold(3);
  const double x[3] = {0.5, -1.2, 2.0};
  double jacobian[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  manifold.PlusJacobian(x, jacobian);
}
