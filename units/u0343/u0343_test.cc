// FILE: u0343_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(QuaternionManifoldPlusJacobianTest, TC1_SinglePath) {
  ceres::QuaternionManifold manifold;
  const double x[4] = {0.5, 0.5, 0.5, 0.5};
  double jacobian[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  manifold.PlusJacobian(x, jacobian);
}
