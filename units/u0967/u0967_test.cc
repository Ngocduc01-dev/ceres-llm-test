// FILE: u0967_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0967, TC1_CallsTarget) {
  int size{};
  ceres::internal::BlockSparseMatrix object{};
  object.AllocateValues(size);
}
