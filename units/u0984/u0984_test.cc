// FILE: u0984_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/tiny_solver_cost_function_adapter.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0984, TC1_CallsTarget) {
  ceres::TinySolverCostFunctionAdapter object{};
  object.NumResiduals();
}
