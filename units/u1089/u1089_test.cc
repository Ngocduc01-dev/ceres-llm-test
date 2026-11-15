// FILE: u1089_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END
TEST(GetResidualBlocksTest, TC1_CallsTarget) {
  ProblemImpl object{};
  object.GetResidualBlocks(nullptr);
}

