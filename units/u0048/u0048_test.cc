// FILE: u0048_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// P1: START -> END (không có điểm rẽ nhánh)
TEST(FixedArrayNonEmptyInlinedStorageTest, AnnotateConstruct_TC1) {
  // NonEmptyInlinedStorage là kiểu private của FixedArray, nên đi qua constructor
  // của FixedArray<int, 20>: constructor này gọi AnnotateConstruct(3) trên storage inline.
  ceres::internal::FixedArray<int, 20> arr(3);
  SUCCEED();
}
