// FILE: u0862_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/implicit_schur_complement.h"

// P1: START -> 1 -> END
TEST(block_diagonal_EtE_inverseTest, TC1_CallsTarget) {
  ImplicitSchurComplement object{};
  object.block_diagonal_EtE_inverse();
}

