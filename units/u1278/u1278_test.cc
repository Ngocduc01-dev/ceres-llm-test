// FILE: u1278_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_minimizer.h"

// P1: START -> 1 -> END
TEST(u1278_Test, TC1_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.MaxSolverTimeReached();
}

// P2: START -> 1 -> END
TEST(u1278_Test, TC2_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.MaxSolverTimeReached();
}

// P3: START -> 1 -> END
TEST(u1278_Test, TC3_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.MaxSolverTimeReached();
}
