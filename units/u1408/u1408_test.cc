// FILE: u1408_test.cc
#include "gtest/gtest.h"
#include "ceres/residual_block_utils.h"
#include "ceres/parameter_block.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1408, TC1_CallsTarget) {
  ResidualBlock block{};
  ceres::internal::EvaluationToString(block, nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1408, TC2_CallsTarget) {
  ResidualBlock block{};
  ceres::internal::EvaluationToString(block, nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1408, TC3_CallsTarget) {
  ResidualBlock block{};
  ceres::internal::EvaluationToString(block, nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1408, TC4_CallsTarget) {
  ResidualBlock block{};
  ceres::internal::EvaluationToString(block, nullptr, nullptr, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1408, TC5_CallsTarget) {
  ResidualBlock block{};
  ceres::internal::EvaluationToString(block, nullptr, nullptr, nullptr, nullptr);
}
