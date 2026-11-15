// FILE: u1466_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/evaluator.h"
#include "ceres/trust_region_minimizer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1466, TC1_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.DoInnerIterationsIfNeeded();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1466, TC2_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.DoInnerIterationsIfNeeded();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1466, TC3_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.DoInnerIterationsIfNeeded();
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1466, TC4_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.DoInnerIterationsIfNeeded();
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1466, TC5_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.DoInnerIterationsIfNeeded();
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1466, TC6_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.DoInnerIterationsIfNeeded();
}
