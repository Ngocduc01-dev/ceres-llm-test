// FILE: u0308_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem_solver.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0308, PathP1) {
  ceres::GradientProblemSolver::Summary target;
  target.IsSolutionUsable();
}
