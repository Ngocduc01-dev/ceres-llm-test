// FILE: u0809_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END
TEST(CreateClusterGraphTest, TC1_CallsTarget) {
  VisibilityBasedPreconditioner object{};
  int a0 = 0;
  object.CreateClusterGraph(a0);
}

// P2: START -> 1 -> END
TEST(CreateClusterGraphTest, TC2_CallsTarget) {
  VisibilityBasedPreconditioner object{};
  int a0 = 0;
  object.CreateClusterGraph(a0);
}

// P3: START -> 1 -> END
TEST(CreateClusterGraphTest, TC3_CallsTarget) {
  VisibilityBasedPreconditioner object{};
  int a0 = 0;
  object.CreateClusterGraph(a0);
}

