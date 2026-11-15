// FILE: u0955_test.cc
#include "gtest/gtest.h"
#include "ceres/cgnr_solver.h"
#include "ceres/dense_normal_cholesky_solver.h"
#include "ceres/dense_qr_solver.h"
#include "ceres/dynamic_sparse_normal_cholesky_solver.h"
#include "ceres/iterative_schur_complement_solver.h"
#include "ceres/linear_solver.h"
#include "ceres/schur_complement_solver.h"
#include "ceres/sparse_normal_cholesky_solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0955, TC1_CallsTarget) {
  LinearSolver::Options options{};
  ceres::internal::LinearSolver object{};
  object.Create(options);
}
