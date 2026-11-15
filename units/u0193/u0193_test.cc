// FILE: u0193_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"

namespace ceres {
namespace internal {

// TC1 - P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(OrderedGroupsIsMemberTest, TC1_P1_NoBranch) {
  OrderedGroups<double*> obj;
  double x = 3.0;
  obj.IsMember(&x);
}

}  // namespace internal
}  // namespace ceres
