// FILE: u0827_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_sparse_matrix.h"
#include "ceres/block_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0827, TC1_CallsTarget) {
  ceres::internal::BlockRandomAccessSparseMatrix object{};
  object.matrix();
}
