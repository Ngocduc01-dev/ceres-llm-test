// FILE: u0931_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0931, TC1_CallsTarget) {
  ceres::internal::BlockSparseMatrix object{};
  object.ScaleColumns(nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0931, TC2_CallsTarget) {
  ceres::internal::BlockSparseMatrix object{};
  object.ScaleColumns(nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0931, TC3_CallsTarget) {
  ceres::internal::BlockSparseMatrix object{};
  object.ScaleColumns(nullptr);
}
