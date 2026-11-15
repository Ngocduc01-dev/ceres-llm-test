// FILE: u0359_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0359, PathP1) {
  ceres::internal::ParameterBlock target;
  target.user_state();
}
