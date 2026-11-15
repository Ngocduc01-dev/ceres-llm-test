// FILE: u0403_test.cc
#include "gtest/gtest.h"
#include "ceres/residual_block.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0403, PathP1) {
  int arg_0 = 1;
  ceres::internal::ResidualBlock target(arg_0);
  target.set_index(1);
}
