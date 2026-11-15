// FILE: u0458_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"

// P1: START -> 1 -> 2 -> 3 -> END (node 2: đúng)
TEST(OrderedGroupsGroupSize, GroupNotFound) {
  ceres::OrderedGroups<double*> obj;
  const int group = 3;
  obj.GroupSize(group);
}

// P2: START -> 1 -> 2 -> 4 -> 3 -> END (node 2: sai)
TEST(OrderedGroupsGroupSize, GroupFound) {
  ceres::OrderedGroups<double*> obj;
  double x = 1.0;
  const int group = 2;
  obj.AddElementToGroup(&x, group);
  obj.GroupSize(group);
}
