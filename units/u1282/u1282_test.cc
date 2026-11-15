// FILE: u1282_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_minimizer.h"

// P1: START -> 1 -> END
TEST(u1282_Test, TC1_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.FunctionToleranceReached();
}

// P2: START -> 1 -> END
TEST(u1282_Test, TC2_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.FunctionToleranceReached();
}

// P3: START -> 1 -> END
TEST(u1282_Test, TC3_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.FunctionToleranceReached();
}
