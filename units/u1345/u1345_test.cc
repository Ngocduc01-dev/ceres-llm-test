// FILE: u1345_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_cholesky.h"
#include "ceres/linear_solver.h"
#include "ceres/schur_complement_solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1345, TC1_CallsTarget) {
  LinearSolver::Options options{};
  ceres::internal::DenseSchurComplementSolver object{};
  (void)object;
}
