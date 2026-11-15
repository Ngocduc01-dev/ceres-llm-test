// FILE: u0044_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(FixedArrayRend, TC1_P1_ConstRend) {
  const ceres::internal::FixedArray<int, 20> arr(3, 7);
  const auto it = arr.rend();
  (void)it;
}
