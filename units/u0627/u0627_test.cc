// FILE: u0627_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"
#include <utility>

// Path P1: START -> 1 -> END.
TEST(Unit_u0627, PathP1) {
  ceres::internal::FixedArray<int, 10> source{1, 2};
  ceres::internal::FixedArray<int, 10> target(std::move(source));
}
