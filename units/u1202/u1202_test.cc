// FILE: u1202_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/inner_product_computer.h"
#include "ceres/small_blas.h"

// P1: START -> 1 -> END
TEST(ComputeTest, TC1_CallsTarget) {
  InnerProductComputer object{};
  object.Compute();
}

// P2: START -> 1 -> END
TEST(ComputeTest, TC2_CallsTarget) {
  InnerProductComputer object{};
  object.Compute();
}

// P3: START -> 1 -> END
TEST(ComputeTest, TC3_CallsTarget) {
  InnerProductComputer object{};
  object.Compute();
}

