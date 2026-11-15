// FILE: u0345_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// Path P1: START -> 1 -> END
TEST(QuaternionManifoldMinusJacobian, TC1_P1_SequentialPath) {
  ceres::QuaternionManifold manifold;
  const double x[4] = {0.5, -0.5, 0.5, -0.5};
  double jacobian[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  manifold.MinusJacobian(x, jacobian);
}
