// FILE: u0601_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0601, CallsTarget) {
  double mutable_blocks_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double block_to_remove_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.DeleteBlockInVector(mutable_blocks_data, block_to_remove_data);
}
