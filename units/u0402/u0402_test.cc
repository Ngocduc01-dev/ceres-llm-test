// FILE: u0402_test.cc
#include "gtest/gtest.h"
#include "ceres/residual_block.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0402, PathP1) {
  ceres::internal::ResidualBlock target;
  target.index();
}
