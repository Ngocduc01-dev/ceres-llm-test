// FILE: u0394_test.cc
#include "gtest/gtest.h"
#include "ceres/program.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0394, PathP1) {
  ceres::internal::Program target;
  target.residual_blocks();
}
