// FILE: u1441_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobi_preconditioner.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/cgnr_solver.h"
#include "ceres/conjugate_gradients_solver.h"
#include "ceres/linear_solver.h"
#include "ceres/preconditioner.h"
#include "ceres/subset_preconditioner.h"
#include "ceres/wall_time.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1441, TC1_CallsTarget) {
  LinearSolver::PerSolveOptions per_solve_options{};
  ceres::internal::CgnrSolver object{};
  object.SolveImpl(nullptr, nullptr, per_solve_options, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1441, TC2_CallsTarget) {
  LinearSolver::PerSolveOptions per_solve_options{};
  ceres::internal::CgnrSolver object{};
  object.SolveImpl(nullptr, nullptr, per_solve_options, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1441, TC3_CallsTarget) {
  LinearSolver::PerSolveOptions per_solve_options{};
  ceres::internal::CgnrSolver object{};
  object.SolveImpl(nullptr, nullptr, per_solve_options, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1441, TC4_CallsTarget) {
  LinearSolver::PerSolveOptions per_solve_options{};
  ceres::internal::CgnrSolver object{};
  object.SolveImpl(nullptr, nullptr, per_solve_options, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1441, TC5_CallsTarget) {
  LinearSolver::PerSolveOptions per_solve_options{};
  ceres::internal::CgnrSolver object{};
  object.SolveImpl(nullptr, nullptr, per_solve_options, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1441, TC6_CallsTarget) {
  LinearSolver::PerSolveOptions per_solve_options{};
  ceres::internal::CgnrSolver object{};
  object.SolveImpl(nullptr, nullptr, per_solve_options, nullptr);
}
