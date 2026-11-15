// FILE: u1037_test.cc
#include "gtest/gtest.h"
#include "ceres/map_util.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END
TEST(SetParameterLowerBoundTest, TC1_CallsTarget) {
  ProblemImpl object{};
  double a0[5] = {};
  int a1 = 0;
  double a2 = 0.0;
  object.SetParameterLowerBound(a0, a1, a2);
}

