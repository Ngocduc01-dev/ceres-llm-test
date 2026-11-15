// FILE: u0192_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(OrderedGroupsClear, P1_ClearNonEmptyGroups) {
  ceres::OrderedGroups<double*> obj;
  double a = 1.0;
  double b = 2.0;
  obj.AddElementToGroup(&a, 3);
  obj.AddElementToGroup(&b, 1);
  obj.Clear();
}
