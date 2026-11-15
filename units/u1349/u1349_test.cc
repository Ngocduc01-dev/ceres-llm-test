// FILE: u1349_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(u1349_Test, TC1_CallsTarget) {
  ceres::internal::BlockSparseMatrix target{};
  target.AddTransposeBlockStructure();
}

// P2: START -> 1 -> END
TEST(u1349_Test, TC2_CallsTarget) {
  ceres::internal::BlockSparseMatrix target{};
  target.AddTransposeBlockStructure();
}
