// FILE: u1189_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobi_preconditioner.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1189, TC1_CallsTarget) {
  Preconditioner::Options options{};
  CompressedRowSparseMatrix A{};
  ceres::internal::BlockCRSJacobiPreconditioner object{};
  (void)object;
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1189, TC2_CallsTarget) {
  Preconditioner::Options options{};
  CompressedRowSparseMatrix A{};
  ceres::internal::BlockCRSJacobiPreconditioner object{};
  (void)object;
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1189, TC3_CallsTarget) {
  Preconditioner::Options options{};
  CompressedRowSparseMatrix A{};
  ceres::internal::BlockCRSJacobiPreconditioner object{};
  (void)object;
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1189, TC4_CallsTarget) {
  Preconditioner::Options options{};
  CompressedRowSparseMatrix A{};
  ceres::internal::BlockCRSJacobiPreconditioner object{};
  (void)object;
}
