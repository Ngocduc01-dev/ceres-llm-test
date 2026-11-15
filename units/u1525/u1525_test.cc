// FILE: u1525_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END
TEST(u1525_Test, TC1_CallsTarget) {
  ceres::Problem target{};
  target.AddParameterBlock(nullptr, nullptr);
}
