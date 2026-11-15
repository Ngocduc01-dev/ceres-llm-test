// FILE: u0440_test.cc
#include "gtest/gtest.h"
TEST(Unit_u0440, Constructor) {
  const double data[2] = {0.0, 1.0};
  ceres::Grid1D<double, 2> target(data, 0, 2);
}
