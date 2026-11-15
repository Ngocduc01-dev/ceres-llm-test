// FILE: u0349_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EigenQuaternionManifoldMinusJacobian, P1_TuanTu) {
  ceres::EigenQuaternionManifold manifold;
  double x[4] = {0.18, -0.42, 0.67, 0.58};
  double jacobian[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  manifold.MinusJacobian(x, jacobian);
}
