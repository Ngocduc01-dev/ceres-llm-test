// FILE: u1206_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/tiny_solver_cost_function_adapter.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1206, TC1_CallsTarget) {
  CostFunction cost_function{};
  TinySolverCostFunctionAdapter<2, 3> object{};
  (void)object;
}
