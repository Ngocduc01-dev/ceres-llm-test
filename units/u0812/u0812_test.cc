// FILE: u0812_test.cc
#include "gtest/gtest.h"
#include "ceres/map_util.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END
TEST(FlattenMembershipMapTest, TC1_CallsTarget) {
  VisibilityBasedPreconditioner object{};
  int a0 = 0;
  int a1[5] = {};
  object.FlattenMembershipMap(a0, a1);
}

// P2: START -> 1 -> END
TEST(FlattenMembershipMapTest, TC2_CallsTarget) {
  VisibilityBasedPreconditioner object{};
  int a0 = 0;
  int a1[5] = {};
  object.FlattenMembershipMap(a0, a1);
}

// P3: START -> 1 -> END
TEST(FlattenMembershipMapTest, TC3_CallsTarget) {
  VisibilityBasedPreconditioner object{};
  int a0 = 0;
  int a1[5] = {};
  object.FlattenMembershipMap(a0, a1);
}

