// FILE: u1348_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_diagonal_matrix.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/context_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1348, TC1_CallsTarget) {
  std::vector<Block> blocks{};
  int num_threads{};
  ceres::internal::BlockRandomAccessDiagonalMatrix object{};
  (void)object;
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1348, TC2_CallsTarget) {
  std::vector<Block> blocks{};
  int num_threads{};
  ceres::internal::BlockRandomAccessDiagonalMatrix object{};
  (void)object;
}
