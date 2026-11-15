// FILE: u1351_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_solver.h"
#include "ceres/schur_complement_solver.h"
#include "ceres/sparse_cholesky.h"

// P1: START -> 1 -> END
TEST(u1351_Test, TC1_CallsTarget) {
  ceres::internal::SparseSchurComplementSolver target{};
}

// P2: START -> 1 -> END
TEST(u1351_Test, TC2_CallsTarget) {
  ceres::internal::SparseSchurComplementSolver target{};
}
