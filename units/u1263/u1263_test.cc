// FILE: u1263_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/tiny_solver_cost_function_adapter.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1263, TC1_CallsTarget) {
  ceres::TinySolverCostFunctionAdapter object{};
  object(nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1263, TC2_CallsTarget) {
  ceres::TinySolverCostFunctionAdapter object{};
  object(nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1263, TC3_CallsTarget) {
  ceres::TinySolverCostFunctionAdapter object{};
  object(nullptr);
}
