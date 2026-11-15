// FILE: u0034_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayBackTest, TC1_BackOnNonEmptyArray) {
  // n = 3 nằm trong [1, 5]; giá trị khởi tạo cố định = 7
  ceres::internal::FixedArray<int, 12> array(3, 7);
  // Gọi unit một lần, không kiểm tra kết quả trả về
  ceres::internal::FixedArray<int, 12>::reference r = array.back();
  (void)r;
}
