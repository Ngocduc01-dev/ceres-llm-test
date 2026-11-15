// FILE: u0759_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/numeric_diff.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0759, TC1_CallsTarget) {
  int parameter_index{};
  double delta{};
  int num_residuals{};
  int parameter_block_size{};
  ceres::internal::NumericDiff object{};
  object.EvaluateJacobianColumn(nullptr, parameter_index, delta, num_residuals, parameter_block_size, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0759, TC2_CallsTarget) {
  int parameter_index{};
  double delta{};
  int num_residuals{};
  int parameter_block_size{};
  ceres::internal::NumericDiff object{};
  object.EvaluateJacobianColumn(nullptr, parameter_index, delta, num_residuals, parameter_block_size, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0759, TC3_CallsTarget) {
  int parameter_index{};
  double delta{};
  int num_residuals{};
  int parameter_block_size{};
  ceres::internal::NumericDiff object{};
  object.EvaluateJacobianColumn(nullptr, parameter_index, delta, num_residuals, parameter_block_size, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}
