// FILE: u0362_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// Path P1: START -> 1 -> END
TEST(ParameterBlockSetVarying, SetVaryingPathP1) {
  double user_state[3] = {1.0, 2.0, 3.0};
  ceres::internal::ParameterBlock parameter_block(user_state, 3, 2);
  parameter_block.SetVarying();
}
