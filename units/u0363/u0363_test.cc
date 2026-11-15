// FILE: u0363_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterBlockIsUpperBoundedTest, TC1_StraightLine) {
  double values[3] = {1.0, 2.0, 3.0};
  ceres::internal::ParameterBlock block(values, 3, 2);
  block.IsUpperBounded();
}
