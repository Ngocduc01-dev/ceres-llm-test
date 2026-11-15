// FILE: u0359_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// TC1 - Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterBlockUserStateTest, ReturnsUserState) {
  double values[3] = {1.5, 2.5, 3.5};
  ParameterBlock block(values, 3, 2);
  const double* state = block.user_state();
  (void)state;  // Không kiểm tra kết quả trả về theo yêu cầu.
}

}  // namespace internal
}  // namespace ceres
