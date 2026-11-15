// FILE: u0560_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"

// Path P1 calls set_num_residuals(int num_residuals).
TEST(Unitu0560, CallsTarget) {
  object.set_num_residuals(1);
}
