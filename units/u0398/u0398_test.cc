// FILE: u0398_test.cc
#include "gtest/gtest.h"
#include "ceres/program.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0398, PathP1) {
  ceres::internal::Program target;
  target.NumResidualBlocks();
}
