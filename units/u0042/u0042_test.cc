// FILE: u0042_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(FixedArrayCrbeginTest, P1_NoBranch) {
  const ceres::internal::FixedArray<int, 20> arr(3, 7);
  auto it = arr.crbegin();
  (void)it;
}
