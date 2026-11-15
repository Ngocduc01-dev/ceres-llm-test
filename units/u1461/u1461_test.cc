// FILE: u1461_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/conjugate_gradients_solver.h"
#include "ceres/implicit_schur_complement.h"
#include "ceres/iterative_schur_complement_solver.h"
#include "ceres/linear_solver.h"
#include "ceres/power_series_expansion_preconditioner.h"
#include "ceres/preconditioner.h"
#include "ceres/wall_time.h"

// P1: START -> 1 -> END
TEST(u1461_Test, TC1_CallsTarget) {
  ceres::internal::IterativeSchurComplementSolver target{};
  target.SolveImpl(nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1461_Test, TC2_CallsTarget) {
  ceres::internal::IterativeSchurComplementSolver target{};
  target.SolveImpl(nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1461_Test, TC3_CallsTarget) {
  ceres::internal::IterativeSchurComplementSolver target{};
  target.SolveImpl(nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1461_Test, TC4_CallsTarget) {
  ceres::internal::IterativeSchurComplementSolver target{};
  target.SolveImpl(nullptr, nullptr, nullptr, nullptr);
}
