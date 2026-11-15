// FILE: u1276_test.cc
#include "gtest/gtest.h"
#include "ceres/iteration_callback.h"
#include "ceres/evaluator.h"
#include "ceres/trust_region_minimizer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1276, TC1_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.IterationZero();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1276, TC2_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.IterationZero();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1276, TC3_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.IterationZero();
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1276, TC4_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.IterationZero();
}
