// FILE: u1067_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluator.h"
#include "ceres/trust_region_minimizer.h"

// P1: START -> 1 -> END
TEST(ComputeCandidatePointAndEvaluateCostTest, TC1_CallsTarget) {
  TrustRegionMinimizer object{};
  object.ComputeCandidatePointAndEvaluateCost();
}

// P2: START -> 1 -> END
TEST(ComputeCandidatePointAndEvaluateCostTest, TC2_CallsTarget) {
  TrustRegionMinimizer object{};
  object.ComputeCandidatePointAndEvaluateCost();
}

// P3: START -> 1 -> END
TEST(ComputeCandidatePointAndEvaluateCostTest, TC3_CallsTarget) {
  TrustRegionMinimizer object{};
  object.ComputeCandidatePointAndEvaluateCost();
}

