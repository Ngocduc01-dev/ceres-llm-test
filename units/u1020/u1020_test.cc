// FILE: u1020_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(NumParameterBlocksTest, TC1_CallsTarget) {
  ResidualBlock object{};
  object.NumParameterBlocks();
}

