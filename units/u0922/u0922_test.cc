// FILE: u0922_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/linear_solver.h"
#include "ceres/partitioned_matrix_view.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0922, TC1_CallsTarget) {
  LinearSolver::Options options{};
  BlockSparseMatrix matrix{};
  ceres::internal::PartitionedMatrixViewBase object{};
  object.Create(options, matrix);
}
