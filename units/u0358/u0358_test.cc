// FILE: u0358_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterBlockStateTest, TC1_ReturnState) {
  double values[3] = {1.5, 2.5, 3.5};
  ceres::internal::ParameterBlock block(values, 3, 2);
  const double* result = block.state();
  (void)result;
}
