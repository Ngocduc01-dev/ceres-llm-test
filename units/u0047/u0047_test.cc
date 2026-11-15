// FILE: u0047_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// TC1 - P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayNonEmptyInlinedStorageData, P1_ReturnBufferPointer) {
  // n = 3 <= 20 nên FixedArray dùng vùng nhớ inline,
  // qua đó gọi NonEmptyInlinedStorage::data().
  ceres::internal::FixedArray<int, 20> array(3);
  (void)array.data();
}
