// FILE: u1203_test.cc
#include "gtest/gtest.h"
#include "ceres/eigensparse.h"
#include "ceres/iterative_refiner.h"
#include "ceres/linear_solver.h"
#include "ceres/sparse_cholesky.h"

// P1: START -> 1 -> END
TEST(CreateTest, TC1_CallsTarget) {
  SparseCholesky object{};
  LinearSolver::Options & options a0{};
  object.Create(a0);
}

// P2: START -> 1 -> END
TEST(CreateTest, TC2_CallsTarget) {
  SparseCholesky object{};
  LinearSolver::Options & options a0{};
  object.Create(a0);
}

// P3: START -> 1 -> END
TEST(CreateTest, TC3_CallsTarget) {
  SparseCholesky object{};
  LinearSolver::Options & options a0{};
  object.Create(a0);
}

