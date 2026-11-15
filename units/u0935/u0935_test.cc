// FILE: u0935_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(Unit_u0935, TC1_CallsTarget) {
  std::ostream & s a0{};
  CompressedRowSparseMatrix::StorageType a1{};
  ceres::internal::operator<<(a0, a1);
}

// P2: START -> 1 -> END
TEST(Unit_u0935, TC2_CallsTarget) {
  std::ostream & s a0{};
  CompressedRowSparseMatrix::StorageType a1{};
  ceres::internal::operator<<(a0, a1);
}

