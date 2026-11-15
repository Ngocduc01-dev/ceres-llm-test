// FILE: u1081_test.cc
#include "gtest/gtest.h"
#include "ceres/reorder_program.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1081, TC1_CallsTarget) {
  std::unordered_set<ResidualBlockId> bottom_residual_blocks{};
  ceres::internal::ReorderResidualBlocksByPartition(bottom_residual_blocks, nullptr);
}
