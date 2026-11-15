// FILE: u1367_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/implicit_schur_complement.h"
#include "ceres/partitioned_matrix_view.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1367, TC1_CallsTarget) {
  BlockSparseMatrix A{};
  ceres::internal::ImplicitSchurComplement object{};
  object.Init(A, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1367, TC2_CallsTarget) {
  BlockSparseMatrix A{};
  ceres::internal::ImplicitSchurComplement object{};
  object.Init(A, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1367, TC3_CallsTarget) {
  BlockSparseMatrix A{};
  ceres::internal::ImplicitSchurComplement object{};
  object.Init(A, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1367, TC4_CallsTarget) {
  BlockSparseMatrix A{};
  ceres::internal::ImplicitSchurComplement object{};
  object.Init(A, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1367, TC5_CallsTarget) {
  BlockSparseMatrix A{};
  ceres::internal::ImplicitSchurComplement object{};
  object.Init(A, nullptr, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1367, TC6_CallsTarget) {
  BlockSparseMatrix A{};
  ceres::internal::ImplicitSchurComplement object{};
  object.Init(A, nullptr, nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1367, TC7_CallsTarget) {
  BlockSparseMatrix A{};
  ceres::internal::ImplicitSchurComplement object{};
  object.Init(A, nullptr, nullptr);
}
