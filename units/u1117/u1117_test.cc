// FILE: u1117_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/eigen.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/schur_eliminator.h"
#include "ceres/schur_eliminator_impl.h"

// P1: START -> 1 -> END
TEST(BackSubstituteTest, TC1_CallsTarget) {
  SchurEliminator object{};
  BlockSparseMatrixData & A a0{};
  double a1[5] = {};
  double a2[5] = {};
  double a3[5] = {};
  double a4[5] = {};
  object.BackSubstitute(a0, a1, a2, a3, a4);
}

