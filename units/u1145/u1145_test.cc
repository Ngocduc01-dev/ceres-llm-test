// FILE: u1145_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/context_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1145, TC1_CallsTarget) {
  int num_threads{};
  ceres::internal::BlockSparseMatrix object{};
  object.SetZero(nullptr, num_threads);
}
