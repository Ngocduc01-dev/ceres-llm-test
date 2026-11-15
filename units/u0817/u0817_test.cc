// FILE: u0817_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END
TEST(manifoldTest, TC1_CallsTarget) {
  GradientProblem object{};
  object.manifold();
}

