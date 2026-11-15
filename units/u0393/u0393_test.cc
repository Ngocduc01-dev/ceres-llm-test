// FILE: u0393_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0393, PathP1) {
  ceres::internal::Program target;
  target.parameter_blocks();
}
