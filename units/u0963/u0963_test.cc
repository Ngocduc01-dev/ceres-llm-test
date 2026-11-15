// FILE: u0963_test.cc
#include "gtest/gtest.h"
#include "ceres/reorder_program.h"
#include "ceres/parameter_block.h"
#include "ceres/triplet_sparse_matrix.h"
#include "ceres/reorder_program.cc"

// P1: START -> 1 -> END
TEST(OrderingForSparseNormalCholeskyUsingSuiteSparseTest, TC1_CallsTarget) {
  LinearSolverOrderingType a0{};
  TripletSparseMatrix & tsm_block_jacobian_transpose a1{};
  ParameterBlockOrdering & parameter_block_ordering a3{};
  int a4[5] = {};
  OrderingForSparseNormalCholeskyUsingSuiteSparse(a0, a1, nullptr, a3, a4);
}

