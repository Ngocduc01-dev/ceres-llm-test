// FILE: u0051_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// TC1 - P1: START -> END (không có điểm rẽ nhánh)
TEST(FixedArrayEmptyInlinedStorageTest, AnnotateConstruct_TC1_P1) {
  // FixedArray<int, 0> dùng EmptyInlinedStorage; constructor gọi
  // AnnotateConstruct(n) đúng một lần. Không kiểm tra kết quả.
  ceres::internal::FixedArray<int, 0> arr(3);
  (void)arr;
}
