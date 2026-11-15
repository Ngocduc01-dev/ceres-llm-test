// FILE: u1394_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_minimizer.h"
#include "ceres/trust_region_strategy.h"

// P1: START -> 1 -> END
TEST(u1394_Test, TC1_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.FinalizeIterationAndCheckIfMinimizerCanContinue();
}

// P2: START -> 1 -> END
TEST(u1394_Test, TC2_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.FinalizeIterationAndCheckIfMinimizerCanContinue();
}

// P3: START -> 1 -> END
TEST(u1394_Test, TC3_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.FinalizeIterationAndCheckIfMinimizerCanContinue();
}

// P4: START -> 1 -> END
TEST(u1394_Test, TC4_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.FinalizeIterationAndCheckIfMinimizerCanContinue();
}
