// FILE: u1280_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_minimizer.h"

// P1: START -> 1 -> END
TEST(u1280_Test, TC1_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.MinTrustRegionRadiusReached();
}

// P2: START -> 1 -> END
TEST(u1280_Test, TC2_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.MinTrustRegionRadiusReached();
}

// P3: START -> 1 -> END
TEST(u1280_Test, TC3_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.MinTrustRegionRadiusReached();
}
