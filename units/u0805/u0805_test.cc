// FILE: u0805_test.cc
#include "gtest/gtest.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END
TEST(ComputeClusterVisibilityTest, TC1_CallsTarget) {
  VisibilityBasedPreconditioner object{};
  int a0 = 0;
  int a1[5] = {};
  object.ComputeClusterVisibility(a0, a1);
}

// P2: START -> 1 -> END
TEST(ComputeClusterVisibilityTest, TC2_CallsTarget) {
  VisibilityBasedPreconditioner object{};
  int a0 = 0;
  int a1[5] = {};
  object.ComputeClusterVisibility(a0, a1);
}

