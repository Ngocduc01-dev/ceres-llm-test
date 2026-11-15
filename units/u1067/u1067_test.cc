// FILE: u1067_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluator.h"
#include "ceres/trust_region_minimizer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1067, TC1_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.ComputeCandidatePointAndEvaluateCost();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1067, TC2_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.ComputeCandidatePointAndEvaluateCost();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1067, TC3_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.ComputeCandidatePointAndEvaluateCost();
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1067, TC4_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.ComputeCandidatePointAndEvaluateCost();
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1067, TC5_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.ComputeCandidatePointAndEvaluateCost();
}
