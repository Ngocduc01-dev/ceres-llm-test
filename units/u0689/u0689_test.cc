// FILE: u0689_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"

// Path P1 calls ~SparseMatrixPreconditionerWrapper().
TEST(Unitu0689, CallsTarget) {
  SparseMatrixPreconditionerWrapper object(matrix_data, {});
}
