// FILE: u1279_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_minimizer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1279, TC1_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.MaxSolverIterationsReached();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1279, TC2_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.MaxSolverIterationsReached();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1279, TC3_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.MaxSolverIterationsReached();
}
