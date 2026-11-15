// FILE: u0368_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0368, PathP1) {
  int arg_0 = 1;
  ceres::internal::ParameterBlock target(arg_0);
  target.set_state_offset(1);
}
