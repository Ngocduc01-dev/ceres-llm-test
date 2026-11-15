// FILE: u0649_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_dense_matrix.h"
#include "ceres/block_random_access_matrix.h"

// Path P1 calls GetCell(const int row_block_id, const int col_block_id, int * row, int * col, int * row_stride, int * col_stride).
TEST(Unitu0649, CallsTarget) {
  double row_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double col_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double row_stride_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double col_stride_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.GetCell(1, 1, row_data, col_data, row_stride_data, col_stride_data);
}
