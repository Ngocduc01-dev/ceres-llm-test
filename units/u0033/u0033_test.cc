// FILE: u0033_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

#include <memory>

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayFrontConstTest, P1_FrontOnConstArray) {
  const ceres::internal::FixedArray<int, 12> array({42, 17, 85},
                                                   std::allocator<int>());
  const int& first = array.front();
  (void)first;  // Không kiểm tra kết quả trả về
}
