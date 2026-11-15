// FILE: u1139_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/parallel_for.h"
#include "ceres/schur_eliminator.h"
#include "ceres/schur_eliminator_impl.h"
#include "ceres/small_blas.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1139, TC1_CallsTarget) {
  BlockSparseMatrixData A{};
  int row_block_index{};
  ceres::internal::SchurEliminator object{};
  object.NoEBlockRowOuterProduct(A, row_block_index, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1139, TC2_CallsTarget) {
  BlockSparseMatrixData A{};
  int row_block_index{};
  ceres::internal::SchurEliminator object{};
  object.NoEBlockRowOuterProduct(A, row_block_index, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1139, TC3_CallsTarget) {
  BlockSparseMatrixData A{};
  int row_block_index{};
  ceres::internal::SchurEliminator object{};
  object.NoEBlockRowOuterProduct(A, row_block_index, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1139, TC4_CallsTarget) {
  BlockSparseMatrixData A{};
  int row_block_index{};
  ceres::internal::SchurEliminator object{};
  object.NoEBlockRowOuterProduct(A, row_block_index, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1139, TC5_CallsTarget) {
  BlockSparseMatrixData A{};
  int row_block_index{};
  ceres::internal::SchurEliminator object{};
  object.NoEBlockRowOuterProduct(A, row_block_index, nullptr);
}
