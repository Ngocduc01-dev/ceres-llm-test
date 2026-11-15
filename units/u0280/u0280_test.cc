// FILE: u0280_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_sparse_matrix.h"

TEST(Unit_u0280, PathP1) {
  // Path P1: START -> 1 -> END.
  ceres::internal::DenseSparseMatrix object(1, 1);
  object.mutable_values();
}
