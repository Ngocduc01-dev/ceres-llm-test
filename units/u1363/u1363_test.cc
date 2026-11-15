// FILE: u1363_test.cc
#include "gtest/gtest.h"
#include "ceres/execution_summary.h"
#include "ceres/linear_operator.h"
#include "ceres/linear_solver.h"

// P1: START -> 1 -> END
TEST(u1363_Test, TC1_CallsTarget) {
  TypedLinearSolver<BlockSparseMatrix> target{};
  target.Solve(nullptr, nullptr, nullptr, nullptr);
}
