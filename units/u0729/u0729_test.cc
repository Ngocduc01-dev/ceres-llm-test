// FILE: u0729_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0729, CallsTarget) {
  double parameter_blocks_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.GetParameterBlocks(parameter_blocks_data);
}
