// FILE: u1538_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem.h"
#include "ceres/gradient_problem_solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1538, TC1_CallsTarget) {
  GradientProblemSolver::Options options{};
  GradientProblem problem{};
  ceres::Solve(options, problem, nullptr, nullptr);
}
