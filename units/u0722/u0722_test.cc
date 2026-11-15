// FILE: u0722_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_sparse_matrix.h"

// Path P1 calls SquaredColumnNorm(double * x) const.
TEST(Unitu0722, CallsTarget) {
  double x_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.SquaredColumnNorm(x_data);
}
