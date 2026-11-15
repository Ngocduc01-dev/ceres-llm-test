// FILE: u0634_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0634, PathP1) {
  ceres::internal::FixedArray<int, 10> left{1}, right{2};
  left >= right;
}
