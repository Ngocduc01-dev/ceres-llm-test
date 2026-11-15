// FILE: u0195_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"

namespace ceres {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(OrderedGroupsNumGroupsTest, P1_DefaultObject) {
  OrderedGroups<double*> obj;
  obj.NumGroups();
}

}  // namespace ceres
