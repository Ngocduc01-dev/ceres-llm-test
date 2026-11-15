// FILE: u0514_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0514, CallsTarget) {
  double f_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.GetValue(1, f_data);
}
