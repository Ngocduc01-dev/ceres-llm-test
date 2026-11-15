// FILE: u0368_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterBlockSetStateOffset, P1_AssignStateOffset) {
  double values[3] = {1.0, 2.0, 3.0};
  ceres::internal::ParameterBlock block(values, 3, 0);
  block.set_state_offset(42);
}
