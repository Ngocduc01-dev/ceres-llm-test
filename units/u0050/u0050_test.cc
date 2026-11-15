// FILE: u0050_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// TC1 - P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayEmptyInlinedStorageData, ReturnsNullptrPath) {
  ceres::internal::FixedArray<int, 0> arr(0);
  arr.data();
}
