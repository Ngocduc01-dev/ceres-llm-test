// FILE: u0045_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// P1: START -> END (không có điểm rẽ nhánh)
TEST(FixedArrayCrendTest, P1_NoBranch) {
  ceres::internal::FixedArray<int, 20> arr(3, 7);
  auto it = arr.crend();
  (void)it;
}
