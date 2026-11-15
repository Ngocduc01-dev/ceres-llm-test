// FILE: u0450_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/sphere_manifold_functions.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0450, PathP1) {
  const VT& arg_0{}
  ceres::internal::ComputeSphereManifoldMinusJacobian<double>(arg_0, nullptr);
}

// Path P2: START -> 1 -> END.
TEST(Unit_u0450, PathP2) {
  const VT& arg_0{}
  ceres::internal::ComputeSphereManifoldMinusJacobian<double>(arg_0, nullptr);
}
