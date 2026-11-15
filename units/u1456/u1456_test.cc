// FILE: u1456_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_qr_solver.h"
#include "ceres/dense_sparse_matrix.h"
#include "ceres/linear_solver.h"
#include "ceres/wall_time.h"

// P1: START -> 1 -> END
TEST(u1456_Test, TC1_CallsTarget) {
  ceres::internal::DenseQRSolver target{};
  target.SolveImpl(nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1456_Test, TC2_CallsTarget) {
  ceres::internal::DenseQRSolver target{};
  target.SolveImpl(nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1456_Test, TC3_CallsTarget) {
  ceres::internal::DenseQRSolver target{};
  target.SolveImpl(nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1456_Test, TC4_CallsTarget) {
  ceres::internal::DenseQRSolver target{};
  target.SolveImpl(nullptr, nullptr, nullptr, nullptr);
}
