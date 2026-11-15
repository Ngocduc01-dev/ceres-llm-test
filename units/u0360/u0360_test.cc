// FILE: u0360_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0360, PathP1) {
  ceres::internal::ParameterBlock target;
  target.mutable_user_state();
}
