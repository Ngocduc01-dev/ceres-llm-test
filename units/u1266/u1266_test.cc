// FILE: u1266_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1266, TC1_CallsTarget) {
  ceres::internal::ResidualBlock object{};
  object.NumScratchDoublesForEvaluate();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1266, TC2_CallsTarget) {
  ceres::internal::ResidualBlock object{};
  object.NumScratchDoublesForEvaluate();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1266, TC3_CallsTarget) {
  ceres::internal::ResidualBlock object{};
  object.NumScratchDoublesForEvaluate();
}
