// FILE: u1123_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/eigen.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/schur_eliminator.h"

// P1: START -> 1 -> END
TEST(EliminateTest, TC1_CallsTarget) {
  SchurEliminatorForOneFBlock object{};
  BlockSparseMatrixData & A a0{};
  double a1[5] = {};
  double a2[5] = {};
  double a4[5] = {};
  object.Eliminate(a0, a1, a2, nullptr, a4);
}

// P2: START -> 1 -> END
TEST(EliminateTest, TC2_CallsTarget) {
  SchurEliminatorForOneFBlock object{};
  BlockSparseMatrixData & A a0{};
  double a1[5] = {};
  double a2[5] = {};
  double a4[5] = {};
  object.Eliminate(a0, a1, a2, nullptr, a4);
}

// P3: START -> 1 -> END
TEST(EliminateTest, TC3_CallsTarget) {
  SchurEliminatorForOneFBlock object{};
  BlockSparseMatrixData & A a0{};
  double a1[5] = {};
  double a2[5] = {};
  double a4[5] = {};
  object.Eliminate(a0, a1, a2, nullptr, a4);
}

