// FILE: u1443_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/linear_solver.h"
#include "ceres/schur_complement_solver.h"
#include "ceres/schur_eliminator.h"
#include "ceres/wall_time.h"

// P1: START -> 1 -> END
TEST(u1443_Test, TC1_CallsTarget) {
  ceres::internal::SchurComplementSolver target{};
  target.SolveImpl(nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1443_Test, TC2_CallsTarget) {
  ceres::internal::SchurComplementSolver target{};
  target.SolveImpl(nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1443_Test, TC3_CallsTarget) {
  ceres::internal::SchurComplementSolver target{};
  target.SolveImpl(nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1443_Test, TC4_CallsTarget) {
  ceres::internal::SchurComplementSolver target{};
  target.SolveImpl(nullptr, nullptr, nullptr, nullptr);
}
