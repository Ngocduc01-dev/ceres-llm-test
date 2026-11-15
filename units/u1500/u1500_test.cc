// FILE: u1500_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1500, TC1_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.RemoveResidualBlock(nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1500, TC2_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.RemoveResidualBlock(nullptr);
}
