// FILE: u0376_test.cc
#include "gtest/gtest.h"
#include "ceres/partitioned_matrix_view.h"
#include "ceres/block_sparse_matrix.h"
// Path P1: START -> 1 -> END.
TEST(Unit_u0376, PathP1) { ceres::LinearSolver::Options options; ceres::internal::CompressedRowBlockStructure* bs = new ceres::internal::CompressedRowBlockStructure; ceres::internal::BlockSparseMatrix matrix(bs); ceres::internal::PartitionedMatrixView<2> target(options, matrix); target.num_cols_f(); }
