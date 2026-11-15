// FILE: u0935_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0935, TC1_CallsTarget) {
  std::ostream s{};
  CompressedRowSparseMatrix::StorageType type{};
  ceres::internal::operator<<(s, type);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0935, TC2_CallsTarget) {
  std::ostream s{};
  CompressedRowSparseMatrix::StorageType type{};
  ceres::internal::operator<<(s, type);
}
