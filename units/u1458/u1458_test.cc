// FILE: u1458_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_sparse_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/casts.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/linear_solver.h"
#include "ceres/schur_complement_solver.h"
#include "ceres/sparse_cholesky.h"

// P1: START -> 1 -> END
TEST(u1458_Test, TC1_CallsTarget) {
  ceres::internal::SparseSchurComplementSolver target{};
  target.SolveReducedLinearSystem(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1458_Test, TC2_CallsTarget) {
  ceres::internal::SparseSchurComplementSolver target{};
  target.SolveReducedLinearSystem(nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1458_Test, TC3_CallsTarget) {
  ceres::internal::SparseSchurComplementSolver target{};
  target.SolveReducedLinearSystem(nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1458_Test, TC4_CallsTarget) {
  ceres::internal::SparseSchurComplementSolver target{};
  target.SolveReducedLinearSystem(nullptr, nullptr);
}
