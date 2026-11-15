// FILE: u1139_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/parallel_for.h"
#include "ceres/schur_eliminator.h"
#include "ceres/schur_eliminator_impl.h"
#include "ceres/small_blas.h"

// P1: START -> 1 -> END
TEST(NoEBlockRowOuterProductTest, TC1_CallsTarget) {
  SchurEliminator object{};
  BlockSparseMatrixData & A a0{};
  int a1 = 0;
  object.NoEBlockRowOuterProduct(a0, a1, nullptr);
}

// P2: START -> 1 -> END
TEST(NoEBlockRowOuterProductTest, TC2_CallsTarget) {
  SchurEliminator object{};
  BlockSparseMatrixData & A a0{};
  int a1 = 0;
  object.NoEBlockRowOuterProduct(a0, a1, nullptr);
}

// P3: START -> 1 -> END
TEST(NoEBlockRowOuterProductTest, TC3_CallsTarget) {
  SchurEliminator object{};
  BlockSparseMatrixData & A a0{};
  int a1 = 0;
  object.NoEBlockRowOuterProduct(a0, a1, nullptr);
}

