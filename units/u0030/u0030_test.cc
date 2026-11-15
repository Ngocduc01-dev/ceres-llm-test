// FILE: u0030_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayDataConst, TC1_P1_ConstData) {
  const ceres::internal::FixedArray<double, 37> arr(3, 1.0);
  const double* p = arr.data();
  (void)p;
}
