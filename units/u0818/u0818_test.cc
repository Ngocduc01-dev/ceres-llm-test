// FILE: u0818_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END
TEST(mutable_manifoldTest, TC1_CallsTarget) {
  GradientProblem object{};
  object.mutable_manifold();
}

