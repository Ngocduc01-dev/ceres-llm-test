// FILE: u1219_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/inner_product_computer.h"

// P1: START -> 1 -> END
TEST(CreateResultMatrixTest, TC1_CallsTarget) {
  InnerProductComputer object{};
  CompressedRowSparseMatrix::StorageType a0{};
  int a1 = 0;
  object.CreateResultMatrix(a0, a1);
}

