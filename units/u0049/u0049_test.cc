// FILE: u0049_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

namespace ceres {
namespace internal {

// P1: START -> END (không có điểm rẽ nhánh)
// AnnotateDestruct được gọi khi FixedArray bị huỷ (kết thúc phạm vi khối bên dưới).
TEST(NonEmptyInlinedStorageAnnotateDestruct, P1_StartToEnd) {
  {
    FixedArray<int, 20> arr(3);
  }
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
