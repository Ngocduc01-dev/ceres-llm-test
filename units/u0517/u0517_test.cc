// FILE: u0517_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/sphere_manifold_functions.h"

// Path P1: START -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> END.
TEST(Unit_u0517, PathP1) {
  Eigen::Matrix<double, 2, 1> v; v << 1.0, 0.0;
  Eigen::Matrix<double, 2, 1> x; x << 1.0, 0.0;
  Eigen::Matrix<double, 2, 1> y; y << 0.0, 1.0;
  Eigen::Matrix<double, 1, 1> y_minus_x;
  ceres::internal::ComputeSphereManifoldMinus(v, 1.0, x, y, &y_minus_x);
}
