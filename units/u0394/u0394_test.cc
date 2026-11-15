// FILE: u0394_test.cc
#include "gtest/gtest.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0394, PathP1) {
  ceres::internal::Program target;
  target.residual_blocks();
}
