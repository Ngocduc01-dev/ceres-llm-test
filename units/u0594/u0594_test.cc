// FILE: u0594_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/compressed_row_sparse_matrix.cc"

// Path P1 calls operator()(const int x, const int y) const.
TEST(Unitu0594, CallsTarget) {
  object.operator(1);
}
