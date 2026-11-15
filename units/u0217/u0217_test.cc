// FILE: u0217_test.cc
#include "gtest/gtest.h"
#include "ceres/sphere_manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(SphereManifoldMinusJacobian, TC1_P1_SinglePath) {
  ceres::SphereManifold<4> manifold;
  const double x[4] = {0.37, -0.62, 0.81, 0.15};
  double jacobian[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  static_cast<void>(manifold.MinusJacobian(x, jacobian));
}
