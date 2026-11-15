// FILE: u1150_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/inner_product_computer.h"

// P1: START -> 1 -> END
TEST(CreateTest, TC1_CallsTarget) {
  InnerProductComputer object{};
  BlockSparseMatrix & m a0{};
  CompressedRowSparseMatrix::StorageType a1{};
  object.Create(a0, a1);
}

