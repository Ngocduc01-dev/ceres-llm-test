// FILE: u1349_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1349, TC1_CallsTarget) {
  ceres::internal::BlockSparseMatrix object{};
  object.AddTransposeBlockStructure();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1349, TC2_CallsTarget) {
  ceres::internal::BlockSparseMatrix object{};
  object.AddTransposeBlockStructure();
}
