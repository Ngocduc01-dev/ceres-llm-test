// FILE: u1021_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(NumResidualsTest, TC1_CallsTarget) {
  ResidualBlock object{};
  object.NumResiduals();
}

