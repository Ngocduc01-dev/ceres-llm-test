// FILE: u1008_test.cc
#include "gtest/gtest.h"
#include "ceres/execution_summary.h"
#include "ceres/linear_solver.h"

// P1: START -> 1 -> END
TEST(StatisticsTest, TC1_CallsTarget) {
  TypedLinearSolver object{};
  object.Statistics();
}

