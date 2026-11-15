// FILE: u1530_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem_solver.h"
#include "ceres/solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1530, TC1_CallsTarget) {
  ceres::GradientProblemSolver::Options object{};
  object.IsValid(nullptr);
}
