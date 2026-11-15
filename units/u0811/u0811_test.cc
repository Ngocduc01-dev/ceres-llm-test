// FILE: u0811_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"
#include "ceres/pair_hash.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END
TEST(ForestToClusterPairsTest, TC1_CallsTarget) {
  VisibilityBasedPreconditioner object{};
  int a0 = 0;
  int a1[5] = {};
  object.ForestToClusterPairs(a0, a1);
}

// P2: START -> 1 -> END
TEST(ForestToClusterPairsTest, TC2_CallsTarget) {
  VisibilityBasedPreconditioner object{};
  int a0 = 0;
  int a1[5] = {};
  object.ForestToClusterPairs(a0, a1);
}

// P3: START -> 1 -> END
TEST(ForestToClusterPairsTest, TC3_CallsTarget) {
  VisibilityBasedPreconditioner object{};
  int a0 = 0;
  int a1[5] = {};
  object.ForestToClusterPairs(a0, a1);
}

