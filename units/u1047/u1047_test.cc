// FILE: u1047_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"

// P1: START -> 1 -> END
TEST(RemoveTest, TC1_CallsTarget) {
  OrderedGroups object{};
  T a0{};
  object.Remove(a0);
}

// P2: START -> 1 -> END
TEST(RemoveTest, TC2_CallsTarget) {
  OrderedGroups object{};
  T a0{};
  object.Remove(a0);
}

// P3: START -> 1 -> END
TEST(RemoveTest, TC3_CallsTarget) {
  OrderedGroups object{};
  T a0{};
  object.Remove(a0);
}

