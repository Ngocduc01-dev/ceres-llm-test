// FILE: u0032_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayFront, SinglePath) {
  // n = 3, val = 42
  ceres::internal::FixedArray<int, 12> array(3, 42);
  int& first = array.front();
  (void)first;
}
