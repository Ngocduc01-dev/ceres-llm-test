// FILE: u1325_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_qr.h"
#include "ceres/dense_qr_solver.h"
#include "ceres/linear_solver.h"

// P1: START -> 1 -> END
TEST(u1325_Test, TC1_CallsTarget) {
  ceres::internal::DenseQRSolver target{};
}
