// FILE: u1102_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1102, TC1_CallsTarget) {
  std::vector<T> elements{};
  ceres::OrderedGroups object{};
  object.Remove(elements);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1102, TC2_CallsTarget) {
  std::vector<T> elements{};
  ceres::OrderedGroups object{};
  object.Remove(elements);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1102, TC3_CallsTarget) {
  std::vector<T> elements{};
  ceres::OrderedGroups object{};
  object.Remove(elements);
}
