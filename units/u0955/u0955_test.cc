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

// P1: START -> 1 -> END
TEST(CreateTest, TC1_CallsTarget) {
  LinearSolver object{};
  LinearSolver::Options & options a0{};
  object.Create(a0);
}

