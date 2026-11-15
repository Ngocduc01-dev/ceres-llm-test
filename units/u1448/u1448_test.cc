// FILE: u1448_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_normal_cholesky_solver.h"
#include "ceres/dense_sparse_matrix.h"
#include "ceres/linear_solver.h"
#include "ceres/wall_time.h"

// P1: START -> 1 -> END
TEST(u1448_Test, TC1_CallsTarget) {
  ceres::internal::DenseNormalCholeskySolver target{};
  target.SolveImpl(nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1448_Test, TC2_CallsTarget) {
  ceres::internal::DenseNormalCholeskySolver target{};
  target.SolveImpl(nullptr, nullptr, nullptr, nullptr);
}
