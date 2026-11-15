// FILE: u0396_test.cc
#include "gtest/gtest.h"
#include "ceres/program.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0396, PathP1) {
  ceres::internal::Program target;
  target.mutable_residual_blocks();
}
