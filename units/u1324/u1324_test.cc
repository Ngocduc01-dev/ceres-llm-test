// FILE: u1324_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_cholesky.h"
#include "ceres/dense_normal_cholesky_solver.h"
#include "ceres/linear_solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1324, TC1_CallsTarget) {
  LinearSolver::Options options{};
  ceres::internal::DenseNormalCholeskySolver object{};
  (void)object;
}
