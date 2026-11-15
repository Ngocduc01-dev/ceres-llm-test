// FILE: u1020_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1020, TC1_CallsTarget) {
  ceres::internal::ResidualBlock object{};
  object.NumParameterBlocks();
}
