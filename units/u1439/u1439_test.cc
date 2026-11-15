// FILE: u1439_test.cc
#include "gtest/gtest.h"
#include "ceres/block_evaluate_preparer.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/casts.h"
#include "ceres/parameter_block.h"
#include "ceres/residual_block.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1439, TC1_CallsTarget) {
  int residual_block_index{};
  ceres::internal::BlockEvaluatePreparer object{};
  object.Prepare(nullptr, residual_block_index, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1439, TC2_CallsTarget) {
  int residual_block_index{};
  ceres::internal::BlockEvaluatePreparer object{};
  object.Prepare(nullptr, residual_block_index, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1439, TC3_CallsTarget) {
  int residual_block_index{};
  ceres::internal::BlockEvaluatePreparer object{};
  object.Prepare(nullptr, residual_block_index, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1439, TC4_CallsTarget) {
  int residual_block_index{};
  ceres::internal::BlockEvaluatePreparer object{};
  object.Prepare(nullptr, residual_block_index, nullptr, nullptr);
}
