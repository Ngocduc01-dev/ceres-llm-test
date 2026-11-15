// FILE: u1342_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END
TEST(u1342_Test, TC1_CallsTarget) {
  ceres::Problem target{};
  target.GetLossFunctionForResidualBlock(nullptr);
}
