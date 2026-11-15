// FILE: u0984_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/tiny_solver_cost_function_adapter.h"

// P1: START -> 1 -> END
TEST(NumResidualsTest, TC1_CallsTarget) {
  TinySolverCostFunctionAdapter object{};
  object.NumResiduals();
}

