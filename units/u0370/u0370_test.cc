// FILE: u0370_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterBlockSetDeltaOffsetTest, TC1_AssignsDeltaOffset) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock block(values, 3, 0);
  block.set_delta_offset(7);
}

}  // namespace internal
}  // namespace ceres
