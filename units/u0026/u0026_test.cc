// FILE: u0026_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayConstructorValTest, TC1_SizeAndValue) {
  const ceres::internal::FixedArray<double>::size_type n = 3;
  const double val = 2.5;
  ceres::internal::FixedArray<double> array(n, val);
}
