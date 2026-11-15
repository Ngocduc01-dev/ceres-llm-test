// FILE: u0028_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArraySizeTest, P1_ReturnsStorageSize) {
  using Array = FixedArray<int, 20>;
  const Array::size_type n = 3;  // giá trị chọn trong khoảng 1..5
  const Array array(n, Array::allocator_type());
  Array::size_type result = array.size();
  (void)result;  // không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
