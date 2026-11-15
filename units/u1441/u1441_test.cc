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

// P1: START -> 1 -> END
TEST(u1441_Test, TC1_CallsTarget) {
  ceres::internal::CgnrSolver target{};
  target.SolveImpl(nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1441_Test, TC2_CallsTarget) {
  ceres::internal::CgnrSolver target{};
  target.SolveImpl(nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1441_Test, TC3_CallsTarget) {
  ceres::internal::CgnrSolver target{};
  target.SolveImpl(nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1441_Test, TC4_CallsTarget) {
  ceres::internal::CgnrSolver target{};
  target.SolveImpl(nullptr, nullptr, nullptr, nullptr);
}
