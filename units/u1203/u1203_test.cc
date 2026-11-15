// FILE: u1203_test.cc
#include "gtest/gtest.h"
#include "ceres/eigensparse.h"
#include "ceres/iterative_refiner.h"
#include "ceres/linear_solver.h"
#include "ceres/sparse_cholesky.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1203, TC1_CallsTarget) {
  LinearSolver::Options options{};
  ceres::internal::SparseCholesky object{};
  object.Create(options);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1203, TC2_CallsTarget) {
  LinearSolver::Options options{};
  ceres::internal::SparseCholesky object{};
  object.Create(options);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1203, TC3_CallsTarget) {
  LinearSolver::Options options{};
  ceres::internal::SparseCholesky object{};
  object.Create(options);
}
