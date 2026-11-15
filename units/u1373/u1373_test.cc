// FILE: u1373_test.cc
#include "gtest/gtest.h"
#include "ceres/reorder_program.h"
#include "ceres/triplet_sparse_matrix.h"
#include "ceres/reorder_program.cc"

// P1: START -> 1 -> END
TEST(u1373_Test, TC1_CallsTarget) {
  OrderingForSparseNormalCholeskyUsingEigenSparse(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1373_Test, TC2_CallsTarget) {
  OrderingForSparseNormalCholeskyUsingEigenSparse(nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1373_Test, TC3_CallsTarget) {
  OrderingForSparseNormalCholeskyUsingEigenSparse(nullptr, nullptr, nullptr);
}
