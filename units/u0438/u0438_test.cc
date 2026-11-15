// FILE: u0438_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_manifold.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0438, PathP1) {
  const double * arg_0 = nullptr;
  double * arg_1 = nullptr;
  ceres::AutoDiffManifold<EuclideanFunctor, 3, 3> target(arg_0, arg_1);
  target.MinusJacobian(nullptr, nullptr);
}

// Path P2: START -> 1 -> END.
TEST(Unit_u0438, PathP2) {
  const double * arg_0 = nullptr;
  double * arg_1 = nullptr;
  ceres::AutoDiffManifold<EuclideanFunctor, 3, 3> target(arg_0, arg_1);
  target.MinusJacobian(nullptr, nullptr);
}
