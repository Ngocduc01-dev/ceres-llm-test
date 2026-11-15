// FILE: u1146_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1146, TC1_CallsTarget) {
  ceres::internal::BlockSparseMatrix object{};
  object.RightMultiplyAndAccumulate(nullptr, nullptr);
}
