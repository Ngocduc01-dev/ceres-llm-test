// FILE: u0304_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0304, PathP1) {
  ceres::GradientProblem target;
  target.NumTangentParameters();
}
