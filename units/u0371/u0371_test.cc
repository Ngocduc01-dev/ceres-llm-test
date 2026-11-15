// FILE: u0371_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterBlockPlusJacobian, P1_NoBranch) {
  double user_state[3] = {0.5, 1.5, 2.5};
  ceres::internal::ParameterBlock block(user_state, 3, 2);
  const double* result = block.PlusJacobian();
  (void)result;
}
