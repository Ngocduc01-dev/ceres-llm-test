// FILE: u1017_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END
TEST(NumParameterBlocksTest, TC1_CallsTarget) {
  ProblemImpl object{};
  object.NumParameterBlocks();
}

