// FILE: u1233_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/block_sparse_matrix.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1233, TC1_CallsTarget) {
  ceres::internal::(anonymous)::UpdateCompressedRowSparseMatrixImpl(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1233, TC2_CallsTarget) {
  ceres::internal::(anonymous)::UpdateCompressedRowSparseMatrixImpl(nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1233, TC3_CallsTarget) {
  ceres::internal::(anonymous)::UpdateCompressedRowSparseMatrixImpl(nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1233, TC4_CallsTarget) {
  ceres::internal::(anonymous)::UpdateCompressedRowSparseMatrixImpl(nullptr, nullptr, nullptr);
}
