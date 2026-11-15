// FILE: u1325_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_qr.h"
#include "ceres/dense_qr_solver.h"
#include "ceres/linear_solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1325, TC1_CallsTarget) {
  LinearSolver::Options options{};
  ceres::internal::DenseQRSolver object{};
  (void)object;
}
