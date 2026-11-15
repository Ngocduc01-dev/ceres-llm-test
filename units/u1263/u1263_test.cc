// FILE: u1263_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/tiny_solver_cost_function_adapter.h"

// P1: START -> 1 -> END
TEST(u1263_Test, TC1_CallsTarget) {
  TinySolverCostFunctionAdapter<2, 3> target{};
  target.operator()(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1263_Test, TC2_CallsTarget) {
  TinySolverCostFunctionAdapter<2, 3> target{};
  target.operator()(nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1263_Test, TC3_CallsTarget) {
  TinySolverCostFunctionAdapter<2, 3> target{};
  target.operator()(nullptr, nullptr, nullptr);
}
