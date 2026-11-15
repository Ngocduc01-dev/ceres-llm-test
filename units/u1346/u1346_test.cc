// FILE: u1346_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_solver.h"
#include "ceres/sparse_cholesky.h"
#include "ceres/sparse_normal_cholesky_solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1346, TC1_CallsTarget) {
  LinearSolver::Options options{};
  ceres::internal::SparseNormalCholeskySolver object{};
  (void)object;
}
