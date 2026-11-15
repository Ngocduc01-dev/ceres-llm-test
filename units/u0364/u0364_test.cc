// FILE: u0364_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// TC1 - P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterBlockIsLowerBounded, TC1_P1_NoBranch) {
  double user_state[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  ceres::internal::ParameterBlock parameter_block(user_state, 3, 0);
  static_cast<void>(parameter_block.IsLowerBounded());
}
