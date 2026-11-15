// FILE: u0663_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_sparse_matrix.h"

// Path P1 calls ToDenseMatrix(Matrix * dense_matrix) const.
TEST(Unitu0663, CallsTarget) {
  double dense_matrix_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.ToDenseMatrix(dense_matrix_data);
}
