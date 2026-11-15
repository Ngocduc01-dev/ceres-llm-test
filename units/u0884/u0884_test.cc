// FILE: u0884_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END
TEST(optionsTest, TC1_CallsTarget) {
  ProblemImpl object{};
  object.options();
}

