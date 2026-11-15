// FILE: u1523_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/loss_function.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END
TEST(u1523_Test, TC1_CallsTarget) {
  ceres::Problem target{};
  target.AddResidualBlock(nullptr, nullptr, nullptr);
}
