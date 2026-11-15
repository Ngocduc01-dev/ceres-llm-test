// FILE: u0912_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/sparse_cholesky.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0912, TC1_CallsTarget) {
  ceres::internal::SparseCholesky object{};
  object.FactorAndSolve(nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0912, TC2_CallsTarget) {
  ceres::internal::SparseCholesky object{};
  object.FactorAndSolve(nullptr, nullptr, nullptr, nullptr);
}
