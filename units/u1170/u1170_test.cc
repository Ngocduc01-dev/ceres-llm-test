// FILE: u1170_test.cc
#include "gtest/gtest.h"
#include "ceres/eigensparse.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1170, TC1_CallsTarget) {
  ceres::internal::EigenSparseCholeskyTemplate object{};
  object.Factorize(nullptr, nullptr);
}
