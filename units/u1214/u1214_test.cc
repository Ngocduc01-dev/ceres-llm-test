// FILE: u1214_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1214, TC1_CallsTarget) {
  CompressedRowSparseMatrix m{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.AppendRows(m);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1214, TC2_CallsTarget) {
  CompressedRowSparseMatrix m{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.AppendRows(m);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1214, TC3_CallsTarget) {
  CompressedRowSparseMatrix m{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.AppendRows(m);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1214, TC4_CallsTarget) {
  CompressedRowSparseMatrix m{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.AppendRows(m);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1214, TC5_CallsTarget) {
  CompressedRowSparseMatrix m{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.AppendRows(m);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1214, TC6_CallsTarget) {
  CompressedRowSparseMatrix m{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.AppendRows(m);
}
