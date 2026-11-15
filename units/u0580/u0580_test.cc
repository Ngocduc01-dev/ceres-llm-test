// FILE: u0580_test.cc
#include "gtest/gtest.h"
#include "ceres/iterative_refiner.h"

// Path P1 calls Allocate(int num_cols).
TEST(Unitu0580, CallsTarget) {
  object.Allocate(1);
}
