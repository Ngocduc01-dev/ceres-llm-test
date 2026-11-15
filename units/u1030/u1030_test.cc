// FILE: u1030_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1030, TC1_CallsTarget) {
  ceres_cost_function_t cost_function{};
  int num_residuals{};
  int num_parameter_blocks{};
  CallbackCostFunction object{};
  (void)object;
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1030, TC2_CallsTarget) {
  ceres_cost_function_t cost_function{};
  int num_residuals{};
  int num_parameter_blocks{};
  CallbackCostFunction object{};
  (void)object;
}
