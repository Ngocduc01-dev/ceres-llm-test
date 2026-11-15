// FILE: u1365_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(u1365_Test, TC1_CallsTarget) {
  ceres::internal::CompressedRowSparseMatrix target{};
  target.LeftMultiplyAndAccumulate(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1365_Test, TC2_CallsTarget) {
  ceres::internal::CompressedRowSparseMatrix target{};
  target.LeftMultiplyAndAccumulate(nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1365_Test, TC3_CallsTarget) {
  ceres::internal::CompressedRowSparseMatrix target{};
  target.LeftMultiplyAndAccumulate(nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1365_Test, TC4_CallsTarget) {
  ceres::internal::CompressedRowSparseMatrix target{};
  target.LeftMultiplyAndAccumulate(nullptr, nullptr);
}
