// FILE: u1234_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluator.h"
#include "ceres/sparse_matrix.h"
#include "ceres/trust_region_minimizer.h"

// P1: START -> 1 -> END
TEST(EvaluateGradientAndJacobianTest, TC1_CallsTarget) {
  TrustRegionMinimizer object{};
  bool a0 = false;
  object.EvaluateGradientAndJacobian(a0);
}

// P2: START -> 1 -> END
TEST(EvaluateGradientAndJacobianTest, TC2_CallsTarget) {
  TrustRegionMinimizer object{};
  bool a0 = false;
  object.EvaluateGradientAndJacobian(a0);
}

// P3: START -> 1 -> END
TEST(EvaluateGradientAndJacobianTest, TC3_CallsTarget) {
  TrustRegionMinimizer object{};
  bool a0 = false;
  object.EvaluateGradientAndJacobian(a0);
}

