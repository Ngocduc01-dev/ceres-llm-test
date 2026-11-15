// FILE: u1156_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END
TEST(GetParameterBlocksTest, TC1_CallsTarget) {
  Problem object{};
  double a0[5] = {};
  object.GetParameterBlocks(a0);
}

