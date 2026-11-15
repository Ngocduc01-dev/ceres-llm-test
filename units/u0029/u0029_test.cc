// FILE: u0029_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayMaxSize, P1_ReturnStatement) {
  ceres::internal::FixedArray<int, 5> arr(3, std::allocator<int>());
  arr.max_size();
}
