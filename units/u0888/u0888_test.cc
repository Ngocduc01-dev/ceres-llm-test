// FILE: u0888_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(cost_functionTest, TC1_CallsTarget) {
  ResidualBlock object{};
  object.cost_function();
}

