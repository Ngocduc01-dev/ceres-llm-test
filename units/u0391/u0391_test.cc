// FILE: u0391_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0391, PathP1) {
  ceres::internal::ProblemImpl target;
  target.mutable_program();
}
