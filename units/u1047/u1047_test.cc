// FILE: u1047_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1047, TC1_CallsTarget) {
  const T element{};
  ceres::OrderedGroups object{};
  object.Remove(element);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1047, TC2_CallsTarget) {
  const T element{};
  ceres::OrderedGroups object{};
  object.Remove(element);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1047, TC3_CallsTarget) {
  const T element{};
  ceres::OrderedGroups object{};
  object.Remove(element);
}
