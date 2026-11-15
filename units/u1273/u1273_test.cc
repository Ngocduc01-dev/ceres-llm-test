// FILE: u1273_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_minimizer.h"
#include "ceres/trust_region_step_evaluator.h"
#include "ceres/trust_region_strategy.h"

// P1: START -> 1 -> END
TEST(u1273_Test, TC1_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.HandleSuccessfulStep();
}

// P2: START -> 1 -> END
TEST(u1273_Test, TC2_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.HandleSuccessfulStep();
}
