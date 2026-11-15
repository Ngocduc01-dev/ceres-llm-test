// FILE: u0043_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(FixedArrayRend, P1_NoBranch) {
  ceres::internal::FixedArray<int, 20> arr({17, 42, 85});
  auto it = arr.rend();
  (void)it;
}
