// FILE: u1279_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_minimizer.h"

// P1: START -> 1 -> END
TEST(u1279_Test, TC1_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.MaxSolverIterationsReached();
}

// P2: START -> 1 -> END
TEST(u1279_Test, TC2_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.MaxSolverIterationsReached();
}

// P3: START -> 1 -> END
TEST(u1279_Test, TC3_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.MaxSolverIterationsReached();
}
