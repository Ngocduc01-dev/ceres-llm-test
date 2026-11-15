// FILE: u1483_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END
TEST(u1483_Test, TC1_CallsTarget) {
  ceres::Problem target{};
  target.EvaluateResidualBlock(nullptr, nullptr, nullptr, nullptr, nullptr);
}
