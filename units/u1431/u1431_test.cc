// FILE: u1431_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END
TEST(u1431_Test, TC1_CallsTarget) {
  ceres::Problem target{};
  target.GetParameterBlocksForResidualBlock(nullptr, nullptr);
}
