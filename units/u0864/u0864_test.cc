// FILE: u0864_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/inner_product_computer.h"

// P1: START -> 1 -> END
TEST(mutable_resultTest, TC1_CallsTarget) {
  InnerProductComputer object{};
  object.mutable_result();
}

