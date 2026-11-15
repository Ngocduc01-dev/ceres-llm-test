// FILE: u0576_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/compressed_row_sparse_matrix.cc"

// Path P1 calls RowColLessThan(const int * rows, const int * cols).
TEST(Unitu0576, CallsTarget) {
  double rows_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double cols_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.RowColLessThan(rows_data, cols_data);
}
