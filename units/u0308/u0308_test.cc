// FILE: u0308_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem_solver.h"
#include "ceres/solver_utils.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0308, PathP1) {
  ceres::GradientProblemSolver::Summary target;
  target.IsSolutionUsable();
}
