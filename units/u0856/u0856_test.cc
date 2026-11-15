// FILE: u0856_test.cc
#include "gtest/gtest.h"
#include "ceres/eigensparse.h"
#include "ceres/compressed_row_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(StorageTypeTest, TC1_CallsTarget) {
  EigenSparseCholeskyTemplate object{};
  object.StorageType();
}

