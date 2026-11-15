// FILE: u0575_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_sparse_matrix.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0575, CallsTarget) {
  double row_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double col_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Int64ToIntPair(1, row_data, col_data);
}
