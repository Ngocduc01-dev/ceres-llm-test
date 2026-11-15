// FILE: u0625_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/autodiff.h"

// Path P1 calls Apply(const T *, JetT *).
TEST(Unitu0625, CallsTarget) {
  double arg0_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double arg1_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Apply(arg0_data, arg1_data);
}
