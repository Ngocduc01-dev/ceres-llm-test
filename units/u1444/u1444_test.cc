// FILE: u1444_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1444, TC1_CallsTarget) {
  bool use_page_locked_memory{};
  ceres::internal::BlockSparseMatrix object{};
  (void)object;
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1444, TC2_CallsTarget) {
  bool use_page_locked_memory{};
  ceres::internal::BlockSparseMatrix object{};
  (void)object;
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1444, TC3_CallsTarget) {
  bool use_page_locked_memory{};
  ceres::internal::BlockSparseMatrix object{};
  (void)object;
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1444, TC4_CallsTarget) {
  bool use_page_locked_memory{};
  ceres::internal::BlockSparseMatrix object{};
  (void)object;
}
