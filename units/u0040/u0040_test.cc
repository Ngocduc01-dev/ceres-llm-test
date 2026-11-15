// FILE: u0040_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// P1: START -> END (không có điểm rẽ nhánh)
TEST(FixedArrayRbeginTest, TC1_NoBranch) {
  ceres::internal::FixedArray<int, 20> arr(3, std::allocator<int>());
  auto it = arr.rbegin();
  (void)it;  // không kiểm tra kết quả trả về
}
