// FILE: u0041_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(FixedArrayRbeginConstTest, P1_ConstRbeginOnSmallArray) {
  using Array = ceres::internal::FixedArray<int, 20>;
  const Array arr(3, 7, Array::allocator_type());
  Array::const_reverse_iterator it = arr.rbegin();
  (void)it;
}
