// FILE: u1143_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobi_preconditioner.h"
#include "ceres/block_random_access_diagonal_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/preconditioner.h"

// P1: START -> 1 -> END
TEST(Unit_u1143, TC1_CallsTarget) {
  BlockSparseJacobiPreconditioner object{};
  Preconditioner::Options a0{};
  BlockSparseMatrix & A a1{};
}

