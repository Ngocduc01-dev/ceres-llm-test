// FILE: u0559_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"

// Path P1 calls mutable_parameter_block_sizes().
TEST(Unitu0559, CallsTarget) {
  object.mutable_parameter_block_sizes();
}
