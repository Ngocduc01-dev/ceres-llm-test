// FILE: u0392_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0392, PathP1) {
  ceres::internal::ProblemImpl target;
  target.parameter_map();
}
