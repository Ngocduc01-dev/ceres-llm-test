// FILE: u0751_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block_ordering.h"
#include "ceres/ordered_groups.h"

// P1: START -> 1 -> END
TEST(OrderingToGroupSizesTest, TC1_CallsTarget) {
  int a1[5] = {};
  ceres::internal::OrderingToGroupSizes(nullptr, a1);
}

// P2: START -> 1 -> END
TEST(OrderingToGroupSizesTest, TC2_CallsTarget) {
  int a1[5] = {};
  ceres::internal::OrderingToGroupSizes(nullptr, a1);
}

// P3: START -> 1 -> END
TEST(OrderingToGroupSizesTest, TC3_CallsTarget) {
  int a1[5] = {};
  ceres::internal::OrderingToGroupSizes(nullptr, a1);
}

