// FILE: u1458_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_sparse_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/casts.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/linear_solver.h"
#include "ceres/schur_complement_solver.h"
#include "ceres/sparse_cholesky.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1458, TC1_CallsTarget) {
  LinearSolver::PerSolveOptions per_solve_options{};
  ceres::internal::SparseSchurComplementSolver object{};
  object.SolveReducedLinearSystem(per_solve_options, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1458, TC2_CallsTarget) {
  LinearSolver::PerSolveOptions per_solve_options{};
  ceres::internal::SparseSchurComplementSolver object{};
  object.SolveReducedLinearSystem(per_solve_options, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1458, TC3_CallsTarget) {
  LinearSolver::PerSolveOptions per_solve_options{};
  ceres::internal::SparseSchurComplementSolver object{};
  object.SolveReducedLinearSystem(per_solve_options, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1458, TC4_CallsTarget) {
  LinearSolver::PerSolveOptions per_solve_options{};
  ceres::internal::SparseSchurComplementSolver object{};
  object.SolveReducedLinearSystem(per_solve_options, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1458, TC5_CallsTarget) {
  LinearSolver::PerSolveOptions per_solve_options{};
  ceres::internal::SparseSchurComplementSolver object{};
  object.SolveReducedLinearSystem(per_solve_options, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1458, TC6_CallsTarget) {
  LinearSolver::PerSolveOptions per_solve_options{};
  ceres::internal::SparseSchurComplementSolver object{};
  object.SolveReducedLinearSystem(per_solve_options, nullptr);
}
