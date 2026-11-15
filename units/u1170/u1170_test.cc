// FILE: u1170_test.cc
#include "gtest/gtest.h"
#include "ceres/eigensparse.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(FactorizeTest, TC1_CallsTarget) {
  EigenSparseCholeskyTemplate object{};
  object.Factorize(nullptr, nullptr);
}

