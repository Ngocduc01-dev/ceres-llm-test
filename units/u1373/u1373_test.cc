// FILE: u1373_test.cc
#include "gtest/gtest.h"
#include "ceres/reorder_program.h"
#include "ceres/triplet_sparse_matrix.h"
#include "ceres/reorder_program.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1373, TC1_CallsTarget) {
  const LinearSolverOrderingType linear_solver_ordering_type{};
  TripletSparseMatrix tsm_block_jacobian_transpose{};
  ceres::internal::(anonymous)::OrderingForSparseNormalCholeskyUsingEigenSparse(linear_solver_ordering_type, tsm_block_jacobian_transpose, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1373, TC2_CallsTarget) {
  const LinearSolverOrderingType linear_solver_ordering_type{};
  TripletSparseMatrix tsm_block_jacobian_transpose{};
  ceres::internal::(anonymous)::OrderingForSparseNormalCholeskyUsingEigenSparse(linear_solver_ordering_type, tsm_block_jacobian_transpose, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1373, TC3_CallsTarget) {
  const LinearSolverOrderingType linear_solver_ordering_type{};
  TripletSparseMatrix tsm_block_jacobian_transpose{};
  ceres::internal::(anonymous)::OrderingForSparseNormalCholeskyUsingEigenSparse(linear_solver_ordering_type, tsm_block_jacobian_transpose, nullptr);
}
