// FILE: u0402_test.cc
#include "gtest/gtest.h"
#include "ceres/residual_block.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0402, PathP1) {
  ceres::internal::ResidualBlock target;
  target.index();
}
