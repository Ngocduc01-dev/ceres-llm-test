// FILE: u0037_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

#include <memory>

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayBeginConst, P1_ReturnData) {
  using Array = ceres::internal::FixedArray<double>;
  const Array array(3, 1.5, std::allocator<double>());
  Array::const_iterator it = array.begin();
  (void)it;
}
