// FILE: u1029_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1029, TC1_CallsTarget) {
  ceres::OrderedGroups object{};
  object.MinNonZeroGroup();
}
