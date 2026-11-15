// FILE: u0347_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EigenQuaternionManifoldPlusJacobianTest, P1_SingleStraightLinePath) {
  ceres::EigenQuaternionManifold manifold;
  // Thứ tự Eigen: (x, y, z, w). Quaternion đơn vị.
  const double x[4] = {0.5, -0.5, 0.5, 0.5};
  // Jacobian kích thước AmbientSize x TangentSize = 4 x 3, lưu theo hàng.
  double jacobian[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  manifold.PlusJacobian(x, jacobian);
}
