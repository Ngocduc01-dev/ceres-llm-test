// FILE: u1378_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_diagonal_matrix.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_random_access_sparse_matrix.h"
#include "ceres/casts.h"
#include "ceres/conjugate_gradients_solver.h"
#include "ceres/linear_solver.h"
#include "ceres/schur_complement_solver.h"

// P1: START -> 1 -> END
TEST(u1378_Test, TC1_CallsTarget) {
  ceres::internal::SparseSchurComplementSolver target{};
  target.SolveReducedLinearSystemUsingConjugateGradients(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1378_Test, TC2_CallsTarget) {
  ceres::internal::SparseSchurComplementSolver target{};
  target.SolveReducedLinearSystemUsingConjugateGradients(nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1378_Test, TC3_CallsTarget) {
  ceres::internal::SparseSchurComplementSolver target{};
  target.SolveReducedLinearSystemUsingConjugateGradients(nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1378_Test, TC4_CallsTarget) {
  ceres::internal::SparseSchurComplementSolver target{};
  target.SolveReducedLinearSystemUsingConjugateGradients(nullptr, nullptr);
}
