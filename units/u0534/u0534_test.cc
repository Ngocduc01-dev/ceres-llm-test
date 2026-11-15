// FILE: u0534_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// Path P1 calls GetValue(const int r, const int c, double * f) const.
TEST(Unitu0534, CallsTarget) {
  double f_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.GetValue(1, 1, f_data);
}
