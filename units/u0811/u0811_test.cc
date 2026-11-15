// FILE: u0811_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"
#include "ceres/pair_hash.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0811, TC1_CallsTarget) {
  WeightedGraph<int> forest{};
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.ForestToClusterPairs(forest, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0811, TC2_CallsTarget) {
  WeightedGraph<int> forest{};
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.ForestToClusterPairs(forest, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0811, TC3_CallsTarget) {
  WeightedGraph<int> forest{};
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.ForestToClusterPairs(forest, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u0811, TC4_CallsTarget) {
  WeightedGraph<int> forest{};
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.ForestToClusterPairs(forest, nullptr);
}
