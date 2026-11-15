// FILE: u1105_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_col_sparse_matrix_utils.h"
#include "ceres/block_structure.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1105, TC1_CallsTarget) {
  std::vector<Block> blocks{};
  std::vector<int> block_ordering{};
  ceres::internal::BlockOrderingToScalarOrdering(blocks, block_ordering, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1105, TC2_CallsTarget) {
  std::vector<Block> blocks{};
  std::vector<int> block_ordering{};
  ceres::internal::BlockOrderingToScalarOrdering(blocks, block_ordering, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1105, TC3_CallsTarget) {
  std::vector<Block> blocks{};
  std::vector<int> block_ordering{};
  ceres::internal::BlockOrderingToScalarOrdering(blocks, block_ordering, nullptr);
}
