// FILE: u0626_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0626, PathP1) {
  ceres::internal::FixedArray<int, 10> source{1, 2};
  ceres::internal::FixedArray<int, 10> target(source);
}
