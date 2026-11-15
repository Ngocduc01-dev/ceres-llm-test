// FILE: u1483_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1483, TC1_CallsTarget) {
  ResidualBlockId residual_block_id{};
  bool apply_loss_function{};
  ceres::Problem object{};
  object.EvaluateResidualBlock(residual_block_id, apply_loss_function, nullptr, nullptr, nullptr);
}
