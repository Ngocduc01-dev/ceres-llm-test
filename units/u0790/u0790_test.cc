// FILE: u0790_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem_solver.h"
#include "ceres/solver.h"
#include "ceres/gradient_problem_solver.cc"

// P1: START -> 1 -> END
TEST(GradientProblemSolverOptionsToSolverOptionsTest, TC1_CallsTarget) {
  GradientProblemSolver::Options & options a0{};
  GradientProblemSolverOptionsToSolverOptions(a0);
}

