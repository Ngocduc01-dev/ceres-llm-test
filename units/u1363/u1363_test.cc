// FILE: u1363_test.cc
#include "gtest/gtest.h"
#include "ceres/execution_summary.h"
#include "ceres/linear_operator.h"
#include "ceres/linear_solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1363, TC1_CallsTarget) {
  LinearSolver::PerSolveOptions per_solve_options{};
  ceres::internal::TypedLinearSolver object{};
  object.Solve(nullptr, nullptr, per_solve_options, nullptr);
}
