// FILE: u0180_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// Path P1: START -> 1 -> END (không có nhánh rẽ)
TEST(EuclideanManifoldPlus, P1_SequentialPath) {
  const int size = 3;
  ceres::EuclideanManifold<ceres::DYNAMIC> manifold(size);

  const double x[size] = {1.5, -2.0, 4.0};
  const double delta[size] = {0.5, 3.0, -1.0};
  double x_plus_delta[size] = {0.0, 0.0, 0.0};

  manifold.Plus(x, delta, x_plus_delta);
}
