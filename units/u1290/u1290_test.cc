// FILE: u1290_test.cc
#include "gtest/gtest.h"
#include "ceres/sparse_cholesky.h"

// P1: START -> 1 -> END
TEST(u1290_Test, TC1_CallsTarget) {
  ceres::internal::RefinedSparseCholesky target{};
  target.Solve(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1290_Test, TC2_CallsTarget) {
  ceres::internal::RefinedSparseCholesky target{};
  target.Solve(nullptr, nullptr, nullptr);
}
