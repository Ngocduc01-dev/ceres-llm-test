// FILE: u0367_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterBlockStateOffsetTest, TC1_ReturnStateOffset) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock parameter_block(values, 3, 2);
  // Chỉ gọi hàm, không kiểm tra kết quả trả về.
  int offset = parameter_block.state_offset();
  (void)offset;
}

}  // namespace internal
}  // namespace ceres
