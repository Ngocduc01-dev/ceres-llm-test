// FILE: u0215_test.cc
#include "gtest/gtest.h"
#include "ceres/sphere_manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(SphereManifoldPlusJacobian, TC1_LinearPath) {
  ceres::SphereManifold<4> manifold;
  const double x[4] = {0.5, -1.0, 1.5, 0.75};
  double jacobian[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  manifold.PlusJacobian(x, jacobian);
}
