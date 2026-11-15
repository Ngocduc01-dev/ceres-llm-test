// FILE: u0457_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"

namespace ceres {

// P1: START -> 1 -> 2 -> 3 -> END (node 2: đúng)
TEST(OrderedGroupsGroupIdTest, ElementNotFound) {
  OrderedGroups<double*> groups;
  double x[2] = {1.0, 2.0};
  groups.GroupId(&x[0]);
}

// P2: START -> 1 -> 2 -> 4 -> END (node 2: sai)
TEST(OrderedGroupsGroupIdTest, ElementFound) {
  OrderedGroups<double*> groups;
  double x[2] = {1.0, 2.0};
  groups.AddElementToGroup(&x[1], 3);
  groups.GroupId(&x[1]);
}

}  // namespace ceres
