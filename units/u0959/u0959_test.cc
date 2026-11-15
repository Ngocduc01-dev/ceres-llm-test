// FILE: u0959_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/dynamic_sparse_normal_cholesky_solver.h"
#include "ceres/linear_solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0959, TC1_CallsTarget) {
  ceres::internal::DynamicSparseNormalCholeskySolver object{};
  object.SolveImplUsingSuiteSparse(nullptr, nullptr);
}
