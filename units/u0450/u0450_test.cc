// FILE: u0450_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/sphere_manifold_functions.h"

// Path P1: START -> 1 -> 2 -> 3 -> 4 -> 2 -> 5 -> END.
TEST(Unit_u0450, PathP1) {
  Eigen::Matrix<double, 4, 1> x;
  x << 1.0, 0.0, 0.0, 0.0;
  Eigen::Matrix<double, 3, 4> jacobian;
  ceres::internal::ComputeSphereManifoldMinusJacobian(x, &jacobian);
}
