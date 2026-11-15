// FILE: u0883_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/loss_function.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END
TEST(AddResidualBlockTest, TC1_CallsTarget) {
  ProblemImpl object{};
  double a2[5] = {};
  object.AddResidualBlock(nullptr, nullptr, a2, nullptr);
}

