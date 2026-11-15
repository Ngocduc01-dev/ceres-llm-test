// FILE: u1284_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(u1284_Test, TC1_CallsTarget) {
  ceres::internal::BlockRandomAccessSparseMatrix target{};
  target.SetZero();
}
