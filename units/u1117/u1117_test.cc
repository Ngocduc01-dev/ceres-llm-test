// FILE: u1117_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/eigen.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/schur_eliminator.h"
#include "ceres/schur_eliminator_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1117, TC1_CallsTarget) {
  BlockSparseMatrixData A{};
  ceres::internal::SchurEliminator object{};
  object.BackSubstitute(A, nullptr, nullptr, nullptr, nullptr);
}
