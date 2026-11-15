// FILE: u1523_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/loss_function.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1523, TC1_CallsTarget) {
  ceres::Problem object{};
  object.AddResidualBlock(nullptr, nullptr, nullptr);
}
