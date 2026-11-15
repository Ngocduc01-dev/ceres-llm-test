// FILE: u1224_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/block_sparse_matrix.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1224, TC1_CallsTarget) {
  ceres::internal::(anonymous)::SetBlockStructureOfCompressedRowSparseMatrix(nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1224, TC2_CallsTarget) {
  ceres::internal::(anonymous)::SetBlockStructureOfCompressedRowSparseMatrix(nullptr, nullptr);
}
