// FILE: u0922_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/linear_solver.h"
#include "ceres/partitioned_matrix_view.h"

// P1: START -> 1 -> END
TEST(CreateTest, TC1_CallsTarget) {
  PartitionedMatrixViewBase object{};
  LinearSolver::Options & options a0{};
  BlockSparseMatrix & matrix a1{};
  object.Create(a0, a1);
}

