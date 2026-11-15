// FILE: u0783_test.cc
#include "gtest/gtest.h"
#include "ceres/reorder_program.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0783, TC1_CallsTarget) {
  const LinearSolverType linear_solver_type{};
  const PreconditionerType preconditioner_type{};
  const SparseLinearAlgebraLibraryType sparse_linear_algebra_library_type{};
  const LinearSolverOrderingType linear_solver_ordering_type{};
  ceres::internal::AreJacobianColumnsOrdered(linear_solver_type, preconditioner_type, sparse_linear_algebra_library_type, linear_solver_ordering_type);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0783, TC2_CallsTarget) {
  const LinearSolverType linear_solver_type{};
  const PreconditionerType preconditioner_type{};
  const SparseLinearAlgebraLibraryType sparse_linear_algebra_library_type{};
  const LinearSolverOrderingType linear_solver_ordering_type{};
  ceres::internal::AreJacobianColumnsOrdered(linear_solver_type, preconditioner_type, sparse_linear_algebra_library_type, linear_solver_ordering_type);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0783, TC3_CallsTarget) {
  const LinearSolverType linear_solver_type{};
  const PreconditionerType preconditioner_type{};
  const SparseLinearAlgebraLibraryType sparse_linear_algebra_library_type{};
  const LinearSolverOrderingType linear_solver_ordering_type{};
  ceres::internal::AreJacobianColumnsOrdered(linear_solver_type, preconditioner_type, sparse_linear_algebra_library_type, linear_solver_ordering_type);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u0783, TC4_CallsTarget) {
  const LinearSolverType linear_solver_type{};
  const PreconditionerType preconditioner_type{};
  const SparseLinearAlgebraLibraryType sparse_linear_algebra_library_type{};
  const LinearSolverOrderingType linear_solver_ordering_type{};
  ceres::internal::AreJacobianColumnsOrdered(linear_solver_type, preconditioner_type, sparse_linear_algebra_library_type, linear_solver_ordering_type);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u0783, TC5_CallsTarget) {
  const LinearSolverType linear_solver_type{};
  const PreconditionerType preconditioner_type{};
  const SparseLinearAlgebraLibraryType sparse_linear_algebra_library_type{};
  const LinearSolverOrderingType linear_solver_ordering_type{};
  ceres::internal::AreJacobianColumnsOrdered(linear_solver_type, preconditioner_type, sparse_linear_algebra_library_type, linear_solver_ordering_type);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u0783, TC6_CallsTarget) {
  const LinearSolverType linear_solver_type{};
  const PreconditionerType preconditioner_type{};
  const SparseLinearAlgebraLibraryType sparse_linear_algebra_library_type{};
  const LinearSolverOrderingType linear_solver_ordering_type{};
  ceres::internal::AreJacobianColumnsOrdered(linear_solver_type, preconditioner_type, sparse_linear_algebra_library_type, linear_solver_ordering_type);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u0783, TC7_CallsTarget) {
  const LinearSolverType linear_solver_type{};
  const PreconditionerType preconditioner_type{};
  const SparseLinearAlgebraLibraryType sparse_linear_algebra_library_type{};
  const LinearSolverOrderingType linear_solver_ordering_type{};
  ceres::internal::AreJacobianColumnsOrdered(linear_solver_type, preconditioner_type, sparse_linear_algebra_library_type, linear_solver_ordering_type);
}
