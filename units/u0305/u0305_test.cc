// FILE: u0305_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem.h"
#include "ceres/manifold.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0305, PathP1) {
  const double * arg_0 = nullptr;
  const double * arg_1 = nullptr;
  double * arg_2 = nullptr;
  ceres::GradientProblem target(arg_0, arg_1, arg_2);
  target.Plus(nullptr, nullptr, nullptr);
}
