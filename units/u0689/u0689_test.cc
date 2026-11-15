// FILE: u0689_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0689, CallsTarget) {
  SparseMatrixPreconditionerWrapper object(matrix_data, {});
}
