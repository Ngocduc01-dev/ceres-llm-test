// FILE: u1105_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_col_sparse_matrix_utils.h"
#include "ceres/block_structure.h"

// P1: START -> 1 -> END
TEST(BlockOrderingToScalarOrderingTest, TC1_CallsTarget) {
  std::vector<Block> & blocks a0{};
  int a1 = 0;
  int a2[5] = {};
  ceres::internal::BlockOrderingToScalarOrdering(a0, a1, a2);
}

// P2: START -> 1 -> END
TEST(BlockOrderingToScalarOrderingTest, TC2_CallsTarget) {
  std::vector<Block> & blocks a0{};
  int a1 = 0;
  int a2[5] = {};
  ceres::internal::BlockOrderingToScalarOrdering(a0, a1, a2);
}

// P3: START -> 1 -> END
TEST(BlockOrderingToScalarOrderingTest, TC3_CallsTarget) {
  std::vector<Block> & blocks a0{};
  int a1 = 0;
  int a2[5] = {};
  ceres::internal::BlockOrderingToScalarOrdering(a0, a1, a2);
}

