// FILE: u0883_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/loss_function.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0883, TC1_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.AddResidualBlock(nullptr, nullptr, nullptr, nullptr);
}
