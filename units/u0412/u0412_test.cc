// FILE: u0412_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0412, PathP1) {
  ceres::Solver::Summary target;
  target.IsSolutionUsable();
}
