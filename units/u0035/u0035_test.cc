// FILE: u0035_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

#include <initializer_list>
#include <memory>

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayBackConst, P1_ReturnLastElement) {
  const ceres::internal::FixedArray<int, 12> array(
      {4, 7, 2}, std::allocator<int>());
  array.back();
}
