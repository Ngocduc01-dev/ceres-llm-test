// FILE: u0356_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterBlockConstructorTest, P1_ConstructWithThreeArgs) {
  double user_state[3] = {1.5, -2.0, 3.25};
  const int size = 3;   // khoảng 1..5, giá trị chọn cố định
  const int index = 2;  // khoảng 0..5, giá trị chọn cố định

  ParameterBlock block(user_state, size, index);
  (void)block;  // không kiểm tra kết quả
}

}  // namespace internal
}  // namespace ceres
