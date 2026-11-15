// FILE: u1432_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END
TEST(u1432_Test, TC1_CallsTarget) {
  ceres::Problem target{};
  target.GetResidualBlocksForParameterBlock(nullptr, nullptr);
}
