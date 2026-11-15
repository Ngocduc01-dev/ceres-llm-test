// FILE: u1200_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_cholesky.h"
#include "ceres/iterative_refiner.h"
#include "ceres/linear_solver.h"

// P1: START -> 1 -> END
TEST(CreateTest, TC1_CallsTarget) {
  DenseCholesky object{};
  LinearSolver::Options & options a0{};
  object.Create(a0);
}

