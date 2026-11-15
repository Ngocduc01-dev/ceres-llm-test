// FILE: u0892_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/sparse_cholesky.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0892, TC1_CallsTarget) {
  ceres::internal::RefinedSparseCholesky object{};
  object.Factorize(nullptr, nullptr);
}
