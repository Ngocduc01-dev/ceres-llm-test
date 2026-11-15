// FILE: u0892_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/sparse_cholesky.h"

// P1: START -> 1 -> END
TEST(FactorizeTest, TC1_CallsTarget) {
  RefinedSparseCholesky object{};
  object.Factorize(nullptr, nullptr);
}

