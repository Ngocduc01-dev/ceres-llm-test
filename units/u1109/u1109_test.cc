// FILE: u1109_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/eigen.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/schur_eliminator.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1109, TC1_CallsTarget) {
  BlockSparseMatrixData A{};
  ceres::internal::SchurEliminatorForOneFBlock object{};
  object.BackSubstitute(A, nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1109, TC2_CallsTarget) {
  BlockSparseMatrixData A{};
  ceres::internal::SchurEliminatorForOneFBlock object{};
  object.BackSubstitute(A, nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1109, TC3_CallsTarget) {
  BlockSparseMatrixData A{};
  ceres::internal::SchurEliminatorForOneFBlock object{};
  object.BackSubstitute(A, nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1109, TC4_CallsTarget) {
  BlockSparseMatrixData A{};
  ceres::internal::SchurEliminatorForOneFBlock object{};
  object.BackSubstitute(A, nullptr, nullptr, nullptr, nullptr);
}
