// FILE: u1530_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem_solver.h"
#include "ceres/solver.h"

// P1: START -> 1 -> END
TEST(u1530_Test, TC1_CallsTarget) {
  ceres::GradientProblemSolver::Options target{};
  target.IsValid(nullptr);
}
