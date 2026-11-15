// FILE: u1249_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END
TEST(NumParametersTest, TC1_CallsTarget) {
  ProblemImpl object{};
  object.NumParameters();
}

