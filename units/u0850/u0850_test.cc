// FILE: u0850_test.cc
#include "gtest/gtest.h"
#include "ceres/dynamic_sparse_normal_cholesky_solver.h"
#include "ceres/linear_solver.h"

// P1: START -> 1 -> END
TEST(Unit_u0850, TC1_CallsTarget) {
  DynamicSparseNormalCholeskySolver object{};
  LinearSolver::Options a0{};
}

