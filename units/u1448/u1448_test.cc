// FILE: u1448_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_normal_cholesky_solver.h"
#include "ceres/dense_sparse_matrix.h"
#include "ceres/linear_solver.h"
#include "ceres/wall_time.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1448, TC1_CallsTarget) {
  LinearSolver::PerSolveOptions per_solve_options{};
  ceres::internal::DenseNormalCholeskySolver object{};
  object.SolveImpl(nullptr, nullptr, per_solve_options, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1448, TC2_CallsTarget) {
  LinearSolver::PerSolveOptions per_solve_options{};
  ceres::internal::DenseNormalCholeskySolver object{};
  object.SolveImpl(nullptr, nullptr, per_solve_options, nullptr);
}
