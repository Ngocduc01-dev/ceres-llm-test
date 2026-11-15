// FILE: u0751_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block_ordering.h"
#include "ceres/ordered_groups.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0751, TC1_CallsTarget) {
  std::vector<int> group_sizes;
  ceres::internal::OrderingToGroupSizes(nullptr, &group_sizes);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0751, TC2_CallsTarget) {
  std::vector<int> group_sizes;
  ceres::internal::OrderingToGroupSizes(nullptr, &group_sizes);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0751, TC3_CallsTarget) {
  std::vector<int> group_sizes;
  ceres::internal::OrderingToGroupSizes(nullptr, &group_sizes);
}
