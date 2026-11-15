// FILE: u0895_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END
TEST(ScaleColumnsTest, TC1_CallsTarget) {
  SparseMatrix object{};
  double a0[5] = {};
  int a2 = 0;
  object.ScaleColumns(a0, nullptr, a2);
}

