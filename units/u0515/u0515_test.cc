// FILE: u0515_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// Path P1 calls Grid2D(const T * data, const int row_begin, const int row_end, const int col_begin, const int col_end).
TEST(Unitu0515, CallsTarget) {
  double data_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Grid2D(data_data, 1, 1, 1, 1);
}
