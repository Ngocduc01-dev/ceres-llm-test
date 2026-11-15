// FILE: u0046_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayFill, SinglePath) {
  ceres::internal::FixedArray<int, 20> arr(3);
  arr.fill(7);
}
