// FILE: u1284_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1284, TC1_CallsTarget) {
  ceres::internal::BlockRandomAccessSparseMatrix object{};
  object.SetZero();
}
