// FILE: u0038_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

#include <memory>

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayCbeginTest, P1_CallCbegin) {
  using Array = ceres::internal::FixedArray<int, 5>;
  Array::allocator_type alloc;
  Array arr({17, 42, 85}, alloc);

  const Array& const_arr = arr;
  Array::const_iterator it = const_arr.cbegin();
  (void)it;
}
