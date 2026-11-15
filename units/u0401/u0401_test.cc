// FILE: u0401_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0401, PathP1) {
  ceres::internal::ResidualBlock target;
  target.parameter_blocks();
}
