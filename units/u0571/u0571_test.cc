// FILE: u0571_test.cc
#include "gtest/gtest.h"
#include "ceres/tiny_solver.h"

// Path P1 calls Initialize(int num_residuals, int num_parameters).
TEST(Unitu0571, CallsTarget) {
  object.Initialize(1, 1);
}
