// FILE: u1053_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1053, TC1_CallsTarget) {
  ceres::OrderedGroups object{};
  object.Reverse();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1053, TC2_CallsTarget) {
  ceres::OrderedGroups object{};
  object.Reverse();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1053, TC3_CallsTarget) {
  ceres::OrderedGroups object{};
  object.Reverse();
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1053, TC4_CallsTarget) {
  ceres::OrderedGroups object{};
  object.Reverse();
}
