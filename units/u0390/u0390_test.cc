// FILE: u0390_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0390, PathP1) {
  ceres::internal::ProblemImpl target;
  target.program();
}
