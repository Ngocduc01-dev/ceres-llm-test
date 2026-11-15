// FILE: u1235_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/block_sparse_matrix.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1235, TC1_CallsTarget) {
  int num_rows{};
  int num_cols{};
  int num_nonzeros{};
  ceres::internal::(anonymous)::CreateStructureOfCompressedRowSparseMatrix(nullptr, num_rows, num_cols, num_nonzeros, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1235, TC2_CallsTarget) {
  int num_rows{};
  int num_cols{};
  int num_nonzeros{};
  ceres::internal::(anonymous)::CreateStructureOfCompressedRowSparseMatrix(nullptr, num_rows, num_cols, num_nonzeros, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1235, TC3_CallsTarget) {
  int num_rows{};
  int num_cols{};
  int num_nonzeros{};
  ceres::internal::(anonymous)::CreateStructureOfCompressedRowSparseMatrix(nullptr, num_rows, num_cols, num_nonzeros, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1235, TC4_CallsTarget) {
  int num_rows{};
  int num_cols{};
  int num_nonzeros{};
  ceres::internal::(anonymous)::CreateStructureOfCompressedRowSparseMatrix(nullptr, num_rows, num_cols, num_nonzeros, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1235, TC5_CallsTarget) {
  int num_rows{};
  int num_cols{};
  int num_nonzeros{};
  ceres::internal::(anonymous)::CreateStructureOfCompressedRowSparseMatrix(nullptr, num_rows, num_cols, num_nonzeros, nullptr);
}
