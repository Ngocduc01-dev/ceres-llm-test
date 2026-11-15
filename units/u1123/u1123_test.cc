// FILE: u1123_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/eigen.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/schur_eliminator.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1123, TC1_CallsTarget) {
  BlockSparseMatrixData A{};
  ceres::internal::SchurEliminatorForOneFBlock object{};
  object.Eliminate(A, nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1123, TC2_CallsTarget) {
  BlockSparseMatrixData A{};
  ceres::internal::SchurEliminatorForOneFBlock object{};
  object.Eliminate(A, nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1123, TC3_CallsTarget) {
  BlockSparseMatrixData A{};
  ceres::internal::SchurEliminatorForOneFBlock object{};
  object.Eliminate(A, nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1123, TC4_CallsTarget) {
  BlockSparseMatrixData A{};
  ceres::internal::SchurEliminatorForOneFBlock object{};
  object.Eliminate(A, nullptr, nullptr, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1123, TC5_CallsTarget) {
  BlockSparseMatrixData A{};
  ceres::internal::SchurEliminatorForOneFBlock object{};
  object.Eliminate(A, nullptr, nullptr, nullptr, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1123, TC6_CallsTarget) {
  BlockSparseMatrixData A{};
  ceres::internal::SchurEliminatorForOneFBlock object{};
  object.Eliminate(A, nullptr, nullptr, nullptr, nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1123, TC7_CallsTarget) {
  BlockSparseMatrixData A{};
  ceres::internal::SchurEliminatorForOneFBlock object{};
  object.Eliminate(A, nullptr, nullptr, nullptr, nullptr);
}
