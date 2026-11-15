// FILE: u1184_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/inner_product_computer.h"

// P1: START -> 1 -> END
TEST(CreateTest, TC1_CallsTarget) {
  InnerProductComputer object{};
  BlockSparseMatrix & m a0{};
  int a1 = 0;
  int a2 = 0;
  CompressedRowSparseMatrix::StorageType a3{};
  object.Create(a0, a1, a2, a3);
}

