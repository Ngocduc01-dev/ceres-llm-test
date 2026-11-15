// FILE: u0304_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem.h"
#include "ceres/manifold.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0304, PathP1) {
  ceres::GradientProblem target;
  target.NumTangentParameters();
}
