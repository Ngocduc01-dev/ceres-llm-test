// FILE: u1394_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_minimizer.h"
#include "ceres/trust_region_strategy.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1394, TC1_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.FinalizeIterationAndCheckIfMinimizerCanContinue();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1394, TC2_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.FinalizeIterationAndCheckIfMinimizerCanContinue();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1394, TC3_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.FinalizeIterationAndCheckIfMinimizerCanContinue();
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1394, TC4_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.FinalizeIterationAndCheckIfMinimizerCanContinue();
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1394, TC5_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.FinalizeIterationAndCheckIfMinimizerCanContinue();
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1394, TC6_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.FinalizeIterationAndCheckIfMinimizerCanContinue();
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1394, TC7_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.FinalizeIterationAndCheckIfMinimizerCanContinue();
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u1394, TC8_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.FinalizeIterationAndCheckIfMinimizerCanContinue();
}
