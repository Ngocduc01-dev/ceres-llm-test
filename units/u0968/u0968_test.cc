// FILE: u0968_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0968, TC1_CallsTarget) {
  ceres::internal::BlockSparseMatrix object{};
  object.FreeValues(nullptr);
}
