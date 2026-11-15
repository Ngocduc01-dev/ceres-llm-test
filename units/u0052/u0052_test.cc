// FILE: u0052_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// P1: START -> END (không có điểm rẽ nhánh)
// EmptyInlinedStorage::AnnotateDestruct được gọi gián tiếp trong destructor
// của FixedArray<int, 0> khi đối tượng ra khỏi phạm vi.
TEST(FixedArrayEmptyInlinedStorageTest, AnnotateDestructPathP1) {
  {
    ceres::internal::FixedArray<int, 0> arr(3);
  }
  SUCCEED();
}
