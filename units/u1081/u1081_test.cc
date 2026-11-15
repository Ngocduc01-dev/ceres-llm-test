// FILE: u1081_test.cc
#include "gtest/gtest.h"
#include "ceres/reorder_program.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(ReorderResidualBlocksByPartitionTest, TC1_CallsTarget) {
  std::unordered_set<ResidualBlockId> & bottom_residual_blocks a0{};
  ceres::internal::ReorderResidualBlocksByPartition(a0, nullptr);
}

