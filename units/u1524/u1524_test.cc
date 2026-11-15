// FILE: u1524_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/loss_function.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1524, TC1_CallsTarget) {
  int num_parameter_blocks{};
  ceres::Problem object{};
  object.AddResidualBlock(nullptr, nullptr, nullptr, num_parameter_blocks);
}
