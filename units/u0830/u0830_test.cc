// FILE: u0830_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"

// P1: START -> 1 -> END
TEST(block_structureTest, TC1_CallsTarget) {
  BlockSparseMatrix object{};
  object.block_structure();
}

