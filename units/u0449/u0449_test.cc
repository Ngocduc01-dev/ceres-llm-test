// FILE: u0449_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/sphere_manifold_functions.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0449, PathP1) {
  const VT& arg_0{}
  ceres::internal::ComputeSphereManifoldPlusJacobian<double>(arg_0, nullptr);
}

// Path P2: START -> 1 -> END.
TEST(Unit_u0449, PathP2) {
  const VT& arg_0{}
  ceres::internal::ComputeSphereManifoldPlusJacobian<double>(arg_0, nullptr);
}
