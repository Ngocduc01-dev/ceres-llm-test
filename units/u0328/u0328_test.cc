// FILE: u0328_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search_minimizer.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0328, PathP1) {
  int arg_0 = 1;
  int arg_1 = 1;
  ceres::internal::LineSearchMinimizer::State target(arg_0, arg_1);
  target.State(1, 1);
}
