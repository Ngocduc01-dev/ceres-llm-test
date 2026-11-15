// FILE: u0027_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// TC1 - P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayIteratorCtorTest, TC1_ConstructFromForwardIteratorRange) {
  const int data[3] = {7, 42, 19};
  const int* first = data;
  const int* last = data + 3;
  ceres::internal::FixedArray<int, 10> arr(first, last);
  (void)arr;
}
