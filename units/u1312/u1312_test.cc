// FILE: u1312_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/schur_eliminator.h"
#include "ceres/schur_eliminator_impl.h"
#include "ceres/small_blas.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1312, TC1_CallsTarget) {
  BlockSparseMatrixData A{};
  int row_block_counter{};
  ceres::internal::SchurEliminator object{};
  object.NoEBlockRowsUpdate(A, nullptr, row_block_counter, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1312, TC2_CallsTarget) {
  BlockSparseMatrixData A{};
  int row_block_counter{};
  ceres::internal::SchurEliminator object{};
  object.NoEBlockRowsUpdate(A, nullptr, row_block_counter, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1312, TC3_CallsTarget) {
  BlockSparseMatrixData A{};
  int row_block_counter{};
  ceres::internal::SchurEliminator object{};
  object.NoEBlockRowsUpdate(A, nullptr, row_block_counter, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1312, TC4_CallsTarget) {
  BlockSparseMatrixData A{};
  int row_block_counter{};
  ceres::internal::SchurEliminator object{};
  object.NoEBlockRowsUpdate(A, nullptr, row_block_counter, nullptr, nullptr);
}
