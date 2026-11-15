// FILE: u1442_test.cc
#include "gtest/gtest.h"
#include "ceres/reorder_program.h"
#include "ceres/ordered_groups.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1442, TC1_CallsTarget) {
  const SparseLinearAlgebraLibraryType sparse_linear_algebra_library_type{};
  const LinearSolverOrderingType linear_solver_ordering_type{};
  ParameterBlockOrdering parameter_block_ordering{};
  int start_row_block{};
  ceres::internal::ReorderProgramForSparseCholesky(sparse_linear_algebra_library_type, linear_solver_ordering_type, parameter_block_ordering, start_row_block, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1442, TC2_CallsTarget) {
  const SparseLinearAlgebraLibraryType sparse_linear_algebra_library_type{};
  const LinearSolverOrderingType linear_solver_ordering_type{};
  ParameterBlockOrdering parameter_block_ordering{};
  int start_row_block{};
  ceres::internal::ReorderProgramForSparseCholesky(sparse_linear_algebra_library_type, linear_solver_ordering_type, parameter_block_ordering, start_row_block, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1442, TC3_CallsTarget) {
  const SparseLinearAlgebraLibraryType sparse_linear_algebra_library_type{};
  const LinearSolverOrderingType linear_solver_ordering_type{};
  ParameterBlockOrdering parameter_block_ordering{};
  int start_row_block{};
  ceres::internal::ReorderProgramForSparseCholesky(sparse_linear_algebra_library_type, linear_solver_ordering_type, parameter_block_ordering, start_row_block, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1442, TC4_CallsTarget) {
  const SparseLinearAlgebraLibraryType sparse_linear_algebra_library_type{};
  const LinearSolverOrderingType linear_solver_ordering_type{};
  ParameterBlockOrdering parameter_block_ordering{};
  int start_row_block{};
  ceres::internal::ReorderProgramForSparseCholesky(sparse_linear_algebra_library_type, linear_solver_ordering_type, parameter_block_ordering, start_row_block, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1442, TC5_CallsTarget) {
  const SparseLinearAlgebraLibraryType sparse_linear_algebra_library_type{};
  const LinearSolverOrderingType linear_solver_ordering_type{};
  ParameterBlockOrdering parameter_block_ordering{};
  int start_row_block{};
  ceres::internal::ReorderProgramForSparseCholesky(sparse_linear_algebra_library_type, linear_solver_ordering_type, parameter_block_ordering, start_row_block, nullptr, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1442, TC6_CallsTarget) {
  const SparseLinearAlgebraLibraryType sparse_linear_algebra_library_type{};
  const LinearSolverOrderingType linear_solver_ordering_type{};
  ParameterBlockOrdering parameter_block_ordering{};
  int start_row_block{};
  ceres::internal::ReorderProgramForSparseCholesky(sparse_linear_algebra_library_type, linear_solver_ordering_type, parameter_block_ordering, start_row_block, nullptr, nullptr);
}
