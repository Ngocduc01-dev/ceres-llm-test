// FILE: u0959_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/dynamic_sparse_normal_cholesky_solver.h"
#include "ceres/linear_solver.h"

// P1: START -> 1 -> END
TEST(SolveImplUsingSuiteSparseTest, TC1_CallsTarget) {
  DynamicSparseNormalCholeskySolver object{};
  double a1[5] = {};
  object.SolveImplUsingSuiteSparse(nullptr, a1);
}

