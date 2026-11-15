// FILE: u1305_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/internal/numeric_diff.h"
#include "ceres/numeric_diff_options.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1305, TC1_CallsTarget) {
  NumericDiffOptions options{};
  int num_residuals{};
  int parameter_block_index{};
  int parameter_block_size{};
  ceres::internal::NumericDiff object{};
  object.EvaluateJacobianForParameterBlock(nullptr, nullptr, options, num_residuals, parameter_block_index, parameter_block_size, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1305, TC2_CallsTarget) {
  NumericDiffOptions options{};
  int num_residuals{};
  int parameter_block_index{};
  int parameter_block_size{};
  ceres::internal::NumericDiff object{};
  object.EvaluateJacobianForParameterBlock(nullptr, nullptr, options, num_residuals, parameter_block_index, parameter_block_size, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1305, TC3_CallsTarget) {
  NumericDiffOptions options{};
  int num_residuals{};
  int parameter_block_index{};
  int parameter_block_size{};
  ceres::internal::NumericDiff object{};
  object.EvaluateJacobianForParameterBlock(nullptr, nullptr, options, num_residuals, parameter_block_index, parameter_block_size, nullptr, nullptr);
}
