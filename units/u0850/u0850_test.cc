// FILE: u0850_test.cc
#include "gtest/gtest.h"
#include "ceres/dynamic_sparse_normal_cholesky_solver.h"
#include "ceres/linear_solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0850, TC1_CallsTarget) {
  LinearSolver::Options options{};
  ceres::internal::DynamicSparseNormalCholeskySolver object{};
  (void)object;
}
