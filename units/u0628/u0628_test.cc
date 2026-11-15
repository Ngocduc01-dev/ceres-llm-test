// FILE: u0628_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0628, PathP1) {
  ceres::internal::FixedArray<int, 10> target{1, 2};
}
