// FILE: u0280_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_sparse_matrix.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0280, PathP1) {
  ceres::internal::DenseSparseMatrix object(1, 1);
  object.mutable_values();
}
