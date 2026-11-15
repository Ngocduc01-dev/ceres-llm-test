// FILE: u0197_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"

namespace ceres {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(OrderedGroupsElementToGroupTest, DefaultObjectReturnsMapReference) {
  OrderedGroups<int> obj;
  const std::map<int, int>& result = obj.element_to_group();
  static_cast<void>(result);  // Không kiểm tra kết quả trả về
}

}  // namespace ceres
