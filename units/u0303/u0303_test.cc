// FILE: u0303_test.cc
#include "gtest/gtest.h"
#include "ceres/first_order_function.h"
#include "ceres/gradient_problem.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0303, PathP1) {
  ceres::GradientProblem target;
  target.NumParameters();
}
