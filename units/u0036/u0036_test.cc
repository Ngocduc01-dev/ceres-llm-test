// FILE: u0036_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayBeginTest, TC1_P1_BeginOnNonEmptyArray) {
  const ceres::internal::FixedArray<double>::size_type n = 3;
  ceres::internal::FixedArray<double> array(n);
  ceres::internal::FixedArray<double>::iterator it = array.begin();
  (void)it;
}
