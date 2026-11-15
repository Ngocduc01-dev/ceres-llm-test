// FILE: u0369_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterBlockDeltaOffsetTest, P1_ReturnDeltaOffset) {
  double user_state[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  ParameterBlock block(user_state, 3, 2);
  block.delta_offset();
}

}  // namespace internal
}  // namespace ceres
