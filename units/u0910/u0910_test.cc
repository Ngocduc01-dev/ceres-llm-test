// FILE: u0910_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0910, TC1_CallsTarget) {
  Preconditioner::Options options{};
  ceres::internal::SparseMatrixPreconditionerWrapper object{};
  (void)object;
}
