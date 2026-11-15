// FILE: u0894_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END
TEST(SquaredColumnNormTest, TC1_CallsTarget) {
  SparseMatrix object{};
  double a0[5] = {};
  int a2 = 0;
  object.SquaredColumnNorm(a0, nullptr, a2);
}

