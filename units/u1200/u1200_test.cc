// FILE: u1200_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_cholesky.h"
#include "ceres/iterative_refiner.h"
#include "ceres/linear_solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1200, TC1_CallsTarget) {
  LinearSolver::Options options{};
  ceres::internal::DenseCholesky object{};
  object.Create(options);
}
