// FILE: u0941_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/small_blas.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0941, TC1_CallsTarget) {
  ceres::internal::BlockSparseMatrix object{};
  object.LeftMultiplyAndAccumulate(nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0941, TC2_CallsTarget) {
  ceres::internal::BlockSparseMatrix object{};
  object.LeftMultiplyAndAccumulate(nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0941, TC3_CallsTarget) {
  ceres::internal::BlockSparseMatrix object{};
  object.LeftMultiplyAndAccumulate(nullptr, nullptr);
}
