// FILE: u0601_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"

// Path P1 calls DeleteBlockInVector(std::vector<Block*>* mutable_blocks, Block* block_to_remove).
TEST(Unitu0601, CallsTarget) {
  double mutable_blocks_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double block_to_remove_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.DeleteBlockInVector(mutable_blocks_data, block_to_remove_data);
}
