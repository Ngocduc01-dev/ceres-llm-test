// FILE: u1272_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_minimizer.h"
#include "ceres/trust_region_strategy.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1272, TC1_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.HandleInvalidStep();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1272, TC2_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.HandleInvalidStep();
}
