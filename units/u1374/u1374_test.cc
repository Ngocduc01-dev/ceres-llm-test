// FILE: u1374_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/inner_product_computer.h"
#include "ceres/sparse_cholesky.h"
#include "ceres/subset_preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1374, TC1_CallsTarget) {
  BlockSparseMatrix A{};
  ceres::internal::SubsetPreconditioner object{};
  object.UpdateImpl(A, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1374, TC2_CallsTarget) {
  BlockSparseMatrix A{};
  ceres::internal::SubsetPreconditioner object{};
  object.UpdateImpl(A, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1374, TC3_CallsTarget) {
  BlockSparseMatrix A{};
  ceres::internal::SubsetPreconditioner object{};
  object.UpdateImpl(A, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1374, TC4_CallsTarget) {
  BlockSparseMatrix A{};
  ceres::internal::SubsetPreconditioner object{};
  object.UpdateImpl(A, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1374, TC5_CallsTarget) {
  BlockSparseMatrix A{};
  ceres::internal::SubsetPreconditioner object{};
  object.UpdateImpl(A, nullptr);
}
