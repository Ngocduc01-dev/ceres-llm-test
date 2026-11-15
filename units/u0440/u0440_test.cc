// FILE: u0440_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// Path P1: START -> 1 -> 2 (đúng: begin < end) -> END
TEST(Grid1DConstructor, BeginLessThanEnd) {
  const int data[5] = {3, 1, 4, 1, 5};
  const int begin = 1;
  const int end = 4;
  ceres::Grid1D<int> grid(data, begin, end);
  (void)grid;
}
