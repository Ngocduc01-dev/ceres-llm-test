// FILE: u0885_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END
TEST(contextTest, TC1_CallsTarget) {
  ProblemImpl object{};
  object.context();
}

