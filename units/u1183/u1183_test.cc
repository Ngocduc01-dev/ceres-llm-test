// FILE: u1183_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_qr.h"
#include "ceres/linear_solver.h"

// P1: START -> 1 -> END
TEST(CreateTest, TC1_CallsTarget) {
  DenseQR object{};
  LinearSolver::Options & options a0{};
  object.Create(a0);
}

