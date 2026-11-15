// FILE: u1370_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(u1370_Test, TC1_CallsTarget) {
  ceres::internal::CompressedRowSparseMatrix target{};
  target.CreateRandomMatrix(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1370_Test, TC2_CallsTarget) {
  ceres::internal::CompressedRowSparseMatrix target{};
  target.CreateRandomMatrix(nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1370_Test, TC3_CallsTarget) {
  ceres::internal::CompressedRowSparseMatrix target{};
  target.CreateRandomMatrix(nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1370_Test, TC4_CallsTarget) {
  ceres::internal::CompressedRowSparseMatrix target{};
  target.CreateRandomMatrix(nullptr, nullptr);
}
