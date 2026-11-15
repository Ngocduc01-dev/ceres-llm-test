// FILE: u1532_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1532, TC1_CallsTarget) {
  ceres_cost_function_t cost_function{};
  ceres_loss_function_t loss_function{};
  int num_residuals{};
  int num_parameter_blocks{};
  ceres_problem_add_residual_block(nullptr, cost_function, nullptr, loss_function, nullptr, num_residuals, num_parameter_blocks, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1532, TC2_CallsTarget) {
  ceres_cost_function_t cost_function{};
  ceres_loss_function_t loss_function{};
  int num_residuals{};
  int num_parameter_blocks{};
  ceres_problem_add_residual_block(nullptr, cost_function, nullptr, loss_function, nullptr, num_residuals, num_parameter_blocks, nullptr, nullptr);
}
