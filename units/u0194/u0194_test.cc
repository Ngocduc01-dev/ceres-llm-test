// FILE: u0194_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(OrderedGroupsNumElements, P1_StraightLine) {
  ceres::OrderedGroups<double*> obj;
  obj.NumElements();
}
