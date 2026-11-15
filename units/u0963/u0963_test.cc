// FILE: u0963_test.cc
#include "gtest/gtest.h"
#include "ceres/reorder_program.h"
#include "ceres/parameter_block.h"
#include "ceres/triplet_sparse_matrix.h"
#include "ceres/reorder_program.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0963, TC1_CallsTarget) {
  const LinearSolverOrderingType linear_solver_ordering_type{};
  TripletSparseMatrix tsm_block_jacobian_transpose{};
  ParameterBlockOrdering parameter_block_ordering{};
  ceres::internal::(anonymous)::OrderingForSparseNormalCholeskyUsingSuiteSparse(linear_solver_ordering_type, tsm_block_jacobian_transpose, nullptr, parameter_block_ordering, nullptr);
}
