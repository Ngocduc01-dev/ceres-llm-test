// FILE: u1283_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_minimizer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1283, TC1_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.GradientToleranceReached();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1283, TC2_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.GradientToleranceReached();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1283, TC3_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.GradientToleranceReached();
}
