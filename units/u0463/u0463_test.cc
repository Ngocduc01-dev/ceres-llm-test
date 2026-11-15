// FILE: u0463_test.cc
#include "gtest/gtest.h"
#include "ceres/sphere_manifold.h"

// Path P1: START -> 1 -> 2 (đúng) -> 3 -> END
TEST(SphereManifoldPlusTest, TC1_ZeroDelta) {
  ceres::SphereManifold<4> manifold;
  const double x[4] = {0.5, 0.5, 0.5, 0.5};
  const double delta[3] = {0.0, 0.0, 0.0};
  double x_plus_delta[4] = {0.0, 0.0, 0.0, 0.0};
  manifold.Plus(x, delta, x_plus_delta);
}

// Path P2: START -> 1 -> 2 (sai) -> 4 -> END
TEST(SphereManifoldPlusTest, TC2_NonZeroDelta) {
  ceres::SphereManifold<4> manifold;
  const double x[4] = {0.5, 0.5, 0.5, 0.5};
  const double delta[3] = {0.3, -0.2, 0.5};
  double x_plus_delta[4] = {0.0, 0.0, 0.0, 0.0};
  manifold.Plus(x, delta, x_plus_delta);
}
