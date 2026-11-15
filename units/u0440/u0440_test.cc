// FILE: u0440_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0440, PathP1) {
  const T * arg_0 = nullptr;
  const int arg_1 = 1;
  const int arg_2 = 1;
  ceres::Grid1D<int> target(arg_0, arg_1, arg_2);
  target.Grid1D<T, kDataDimension, kInterleaved>(nullptr, 1, 1);
}
