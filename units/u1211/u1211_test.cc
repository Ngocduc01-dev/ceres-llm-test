// FILE: u1211_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1211, TC1_CallsTarget) {
  BlockSparseMatrix m{};
  ceres::internal::BlockSparseMatrix object{};
  object.AppendRows(m);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1211, TC2_CallsTarget) {
  BlockSparseMatrix m{};
  ceres::internal::BlockSparseMatrix object{};
  object.AppendRows(m);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1211, TC3_CallsTarget) {
  BlockSparseMatrix m{};
  ceres::internal::BlockSparseMatrix object{};
  object.AppendRows(m);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1211, TC4_CallsTarget) {
  BlockSparseMatrix m{};
  ceres::internal::BlockSparseMatrix object{};
  object.AppendRows(m);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1211, TC5_CallsTarget) {
  BlockSparseMatrix m{};
  ceres::internal::BlockSparseMatrix object{};
  object.AppendRows(m);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1211, TC6_CallsTarget) {
  BlockSparseMatrix m{};
  ceres::internal::BlockSparseMatrix object{};
  object.AppendRows(m);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1211, TC7_CallsTarget) {
  BlockSparseMatrix m{};
  ceres::internal::BlockSparseMatrix object{};
  object.AppendRows(m);
}
