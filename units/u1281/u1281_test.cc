// FILE: u1281_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_minimizer.h"

// P1: START -> 1 -> END
TEST(u1281_Test, TC1_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.ParameterToleranceReached();
}

// P2: START -> 1 -> END
TEST(u1281_Test, TC2_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.ParameterToleranceReached();
}

// P3: START -> 1 -> END
TEST(u1281_Test, TC3_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.ParameterToleranceReached();
}
