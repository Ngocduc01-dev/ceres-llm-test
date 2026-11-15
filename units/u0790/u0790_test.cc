// FILE: u0790_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem_solver.h"
#include "ceres/solver.h"
#include "ceres/gradient_problem_solver.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0790, TC1_CallsTarget) {
  GradientProblemSolver::Options options{};
  ceres::GradientProblemSolverOptionsToSolverOptions(options);
}
