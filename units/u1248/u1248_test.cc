// FILE: u1248_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END
TEST(HasManifoldTest, TC1_CallsTarget) {
  ProblemImpl object{};
  double a0[5] = {};
  object.HasManifold(a0);
}

