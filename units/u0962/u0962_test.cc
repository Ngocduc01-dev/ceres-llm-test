// FILE: u0962_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END
TEST(UpdateImplTest, TC1_CallsTarget) {
  SparseMatrixPreconditionerWrapper object{};
  SparseMatrix & a0{};
  double a1[5] = {};
  object.UpdateImpl(a0, a1);
}

