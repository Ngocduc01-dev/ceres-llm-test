// FILE: u0889_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(loss_functionTest, TC1_CallsTarget) {
  ResidualBlock object{};
  object.loss_function();
}

