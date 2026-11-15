// FILE: u1228_test.cc
#include "gtest/gtest.h"
#include "ceres/reorder_program.h"
#include "ceres/triplet_sparse_matrix.h"
#include "ceres/reorder_program.cc"

// P1: START -> 1 -> END
TEST(CreateBlockJacobianTest, TC1_CallsTarget) {
  TripletSparseMatrix & block_jacobian_transpose a0{};
  CreateBlockJacobian(a0);
}

// P2: START -> 1 -> END
TEST(CreateBlockJacobianTest, TC2_CallsTarget) {
  TripletSparseMatrix & block_jacobian_transpose a0{};
  CreateBlockJacobian(a0);
}

