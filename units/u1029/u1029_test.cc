// FILE: u1029_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"

// P1: START -> 1 -> END
TEST(MinNonZeroGroupTest, TC1_CallsTarget) {
  OrderedGroups object{};
  object.MinNonZeroGroup();
}

