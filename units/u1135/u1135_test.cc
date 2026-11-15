// FILE: u1135_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/eigen.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/parallel_for.h"
#include "ceres/schur_eliminator.h"
#include "ceres/schur_eliminator_impl.h"

// P1: START -> 1 -> END
TEST(UpdateRhsTest, TC1_CallsTarget) {
  SchurEliminator object{};
  Chunk & chunk a0{};
  BlockSparseMatrixData & A a1{};
  double a2[5] = {};
  int a3 = 0;
  double a4[5] = {};
  double a5[5] = {};
  object.UpdateRhs(a0, a1, a2, a3, a4, a5);
}

// P2: START -> 1 -> END
TEST(UpdateRhsTest, TC2_CallsTarget) {
  SchurEliminator object{};
  Chunk & chunk a0{};
  BlockSparseMatrixData & A a1{};
  double a2[5] = {};
  int a3 = 0;
  double a4[5] = {};
  double a5[5] = {};
  object.UpdateRhs(a0, a1, a2, a3, a4, a5);
}

// P3: START -> 1 -> END
TEST(UpdateRhsTest, TC3_CallsTarget) {
  SchurEliminator object{};
  Chunk & chunk a0{};
  BlockSparseMatrixData & A a1{};
  double a2[5] = {};
  int a3 = 0;
  double a4[5] = {};
  double a5[5] = {};
  object.UpdateRhs(a0, a1, a2, a3, a4, a5);
}

